#include "Server.h"

namespace TX {

	Server::Server()
	{
		serverName = "";
		fileName = "psw.txt";
		Initial();
	}


	Server::~Server()
	{
	}

	void Server::Bind( unsigned port)
	{
		localAddr.addr_4 = "127.0.0.1"; // no matter ,this value would be changed
		localAddr.port = port;
		BindConfig(localAddr);
	}

	void Server::BroadCast(std::string s)
	{
		broadCastAddr.addr_4 = "255.255.255.255";
		broadCastAddr.port = 5020;
		sockaddr_in baddr = MakeRawSocketAddr(broadCastAddr);
		int so_broadcast = 1;
		setsockopt(GetSocket(), SOL_SOCKET, SO_BROADCAST, (const char*)&so_broadcast, sizeof(int));
		SendTo(broadCastAddr, s);
	}

	void Server::Run()
	{
		std::cout << "Server is running..." << std::endl;
		std::string recv = "";
		while (1) {
			recv = ReceiveMsg();
			if (recv != "") {
				if (recv[0] == '*') {  //meaning: exit  protocol: [*(IP):(ACCOUNT)]
					std::string ip, account;
					for (int i = 1;i < recv.length();++i) {
						if (recv[i] == ':') {
							ip = recv.substr(1, i - 1);
							account = recv.substr(i + 1);
							break;
						}
					}
					if (loginTable.find(account) == loginTable.end())
						continue;
					ConsoleMsg(account +" logout.");
					loginTable.erase(account);
					BroadCast(recv); // send back the exit msg
					ReceiveMsg(); // eat the broadcast
					recv = ""; // reset recv
					continue;
				}
				if (recv[0] == 'L') {	//meaning: login protocol: [L(IP):(ACOUNT),(PASSWORD)]
					std::string ip, account, password;
					for (int j = 1,i = 1; i < recv.length(); i++) {
						if (recv[i] == ':') {
							j = i + 1;
							ip = recv.substr(1, i-1);
						}
						if (recv[i] == ',') {
							account = recv.substr(j, i -j); 
							password = recv.substr(i + 1);
							break;
						}
					}
					if (Verify(account, password)) {
						SendByAddr(ip, "Login200");
						ConsoleMsg(account + " login.");
						loginTable[account] = ip;
						BroadCast(account + " login.");
						ReceiveMsg();
						recv = "";
					} else {
						ConsoleMsg(ip + " login fail.");
						SendByAddr(ip,"Server: Error,please input agian.");
					}
					recv = "";
					continue;
				}
				if (recv[0] == 'R') {	//register	[R(IP):(ACOUNT),(PASSWORD)]
					std::string ip, account, password;
					for (int j = 1, i = 1; i < recv.length(); i++) {
						if (recv[i] == ':') {
							j = i + 1;
							ip = recv.substr(1, i - 1);
						}
						if (recv[i] == ',') {
							account = recv.substr(j, i - j);
							password = recv.substr(i + 1);
							break;
						}
					}
					Register(account, password);
					SendByAddr(ip, "Server: Register succuess.");
					recv = "";
					continue;
				}
				if (recv[0] == 'M') {	//deal with msg		
					if (recv[1] == '0') { // public chat msg	[M0(MSG)]
						BroadCast(recv.substr(2));
						ReceiveMsg(); //eat
						ConsoleMsg(recv.substr(2));
						recv = "";
						continue;
					}
					if (recv[1] == '1') { // private chat msg	[M1(ACCOUNT):(MSG)]
						std::string ip = "", msg, account;
						for (int i = 2;i < recv.length();++i) {
							if (recv[i] == ':') {
								account = recv.substr(2, i - 2);
								if (!loginTable.count(account))
								{
									ConsoleMsg(account+",this user didn't exist.");
									break;
								}
								ip = loginTable[account];
								msg = recv.substr(i+1);
								break;
							}
						}
						if (ip == "")
							continue;
						SendByAddr(ip,"{Private}"+msg);
						ConsoleMsg("{Private}"+msg);
						recv = "";
						continue;
					}
				}
				if (recv[0] == 'Q') { // query logintable  [Q(IP)]
					SendLoginTable(recv.substr(1));
					recv = "";
					continue;
				}
				ConsoleMsg("Erorr msg.");
				ConsoleMsg(recv);
				recv = "";
			}
		}
	}

	bool Server::Verify(std::string a, std::string p)
	{
		std::fstream in;
		in.open(fileName, std::ios::in );
		if (!in.is_open())
		{
			Error("storage file opened fail.");
			exit(1);
		}
		char buffer[256];
		bool res = false;
		while (!in.eof()) {
			std::string s,acn,psw;
			in.getline(buffer,100);
			s = buffer;
			for (int i = 0;i < s.length();++i) {
				if (s[i] == ',') {
					acn = s.substr(0,i);
					psw = s.substr(i+1);
					if (acn == a && psw == p)
					{
						res = true;
						break;
					}
				}
			}
		}
		in.close();
		return res;
	}

	void Server::SendByAddr(std::string addr, std::string s)
	{
		socket_addr saddr;
		saddr.addr_4 = addr;
		saddr.port = 5020;
		SendTo(saddr, s);
	}

	void Server::Register(std::string ac, std::string psw)
	{
		std::fstream out;
		out.open(fileName, std::ios::in | std::ios::out| std::ios::ate);
		out << ac << "," << psw<<std::endl;
		out.close();
	}

	void Server::SendLoginTable(std::string addr)
	{
		std::string msg = "Server: ";
		for (auto it : loginTable) {
			msg = msg + it.first + " ";
		}
		SendByAddr(addr,msg);
	}

}