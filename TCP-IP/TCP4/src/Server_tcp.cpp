#include "Server_tcp.h"

namespace TX
{
	void Debug_printvec(vector<pair<SOCKET, string> > &t);
	Server_tcp* g_server;

	DWORD WINAPI  ThreadHandle(LPVOID pM);

	// this thread will never quit
	DWORD WINAPI  ThreadAccept(LPVOID pM)
	{
		Server_tcp* t_server = (Server_tcp *)pM; //no use
		int i = 0;
		std::pair<SOCKET, string>* tmp = new std::pair<SOCKET, string>;
		while (i < 5)
		{
			if (g_server->AcceptConfig(tmp))
			{
				g_server->conn_list.push_back(*tmp);
				++i;
				HANDLE handle_obj = CreateThread(NULL, 0, ThreadHandle, (LPVOID)(tmp->first), 0, NULL);
				if (handle_obj == NULL)
				{
					Error("creat thread failed");
				}
				tmp = new std::pair<SOCKET, string>;
			}
			else
				continue;
		}
		return 0;
	}

	DWORD WINAPI  ThreadHandle(LPVOID pM)
	{

		Error("gennered a thread");
		SOCKET conn = (SOCKET)pM;

		string recv = "";
		while (1)
		{
			recv = g_server->ReceiveMsg(conn);

			if (recv != "")
			{
				if (recv[0] == '*')
				{  //meaning: exit  protocol: [*(IP):(ACCOUNT)]
					string ip, account;
					for (size_t i = 1;i < recv.length();++i)
					{
						if (recv[i] == ':')
						{
							ip = recv.substr(1, i - 1);
							account = recv.substr(i + 1);
							break;
						}
					}
					if (g_server->loginTable.find(account) == g_server->loginTable.end())
						continue;
					ConsoleMsg(account + " logout.");
					g_server->loginTable.erase(account);
					g_server->BroadCast(recv); // send back the exit msg
					vector<pair<SOCKET, string> >::iterator iter;
					//// erase conn
					//for (iter = g_server->conn_list.begin();iter != g_server->conn_list.end();iter++)
					//{
					//	if ((iter->first == conn))
					//	{
					//		g_server->conn_list.erase(iter);
					//		break;
					//	}
					//}
					recv = ""; // reset recv
					break;
				}
				if (recv[0] == 'L')
				{	//meaning: login protocol: [L(IP):(ACOUNT),(PASSWORD)]
					string ip, account, password;
					for (size_t j = 1, i = 1; i < recv.length(); i++)
					{
						if (recv[i] == ':')
						{
							j = i + 1;
							ip = recv.substr(1, i - 1);
						}
						if (recv[i] == ',')
						{
							account = recv.substr(j, i - j);
							password = recv.substr(i + 1);
							break;
						}
					}
					if (g_server->Verify(account, password))
					{
						g_server->SendByAddr(ip, "Login200");
						ConsoleMsg(account + " login.");
						g_server->loginTable[account] = ip;
						g_server->conn_list.push_back(pair<SOCKET,string>(conn,ip));
						g_server->BroadCast(account + " login.");
						recv = "";
					}
					else
					{
						ConsoleMsg(ip + " login fail.");
						g_server->conn_list.push_back(pair<SOCKET, string>(conn, ip));
						g_server->SendByAddr(ip, "Server: User msg Error,please input agian.");
					}
					recv = "";
					continue;
				}
				if (recv[0] == 'R')
				{	//register	[R(IP):(ACOUNT),(PASSWORD)]
					string ip, account, password;
					for (size_t j = 1, i = 1; i < recv.length(); i++)
					{
						if (recv[i] == ':')
						{
							j = i + 1;
							ip = recv.substr(1, i - 1);
						}
						if (recv[i] == ',')
						{
							account = recv.substr(j, i - j);
							password = recv.substr(i + 1);
							break;
						}
					}
					g_server->Register(account, password);
					g_server->SendByAddr(ip, "Server: Register succuess.");
					recv = "";
					continue;
				}
				if (recv[0] == 'M')
				{	//deal with msg		
					if (recv[1] == '0')
					{ // public chat msg	[M0(MSG)]
						g_server->BroadCast(recv.substr(2));
						ConsoleMsg(recv.substr(2));
						recv = "";
						continue;
					}
					if (recv[1] == '1')
					{ // private chat msg	[M1(ACCOUNT):(MSG)]
						string ip = "", msg, account;
						for (size_t i = 2;i < recv.length();++i)
						{
							if (recv[i] == ':')
							{
								account = recv.substr(2, i - 2);
								if (!g_server->loginTable.count(account))
								{
									ConsoleMsg(account + ",this user didn't exist.");
									break;
								}
								ip = g_server->loginTable[account];
								msg = recv.substr(i + 1);
								break;
							}
						}
						if (ip == "")
							continue;
						g_server->SendByAddr(ip, "{Private}" + msg);
						ConsoleMsg("{Private}" + msg);
						recv = "";
						continue;
					}
				}
				if (recv[0] == 'Q')
				{ // query logintable  [Q(IP)]
					g_server->SendLoginTable(recv.substr(1));
					recv = "";
					continue;
				}
				ConsoleMsg("Received an erorr msg.");
				ConsoleMsg(recv);
				recv = "";
			}
			else 
				break;
		}
		return 0;
	}
	void Server_tcp::Run()
	{
		cout << "Server start" << endl;
		// creat accept loop thread
		HANDLE handle_accept = CreateThread(NULL, 0, ThreadAccept, (LPVOID)this, 0, NULL);
		if (handle_accept == NULL)
		{
			Error("creat thread failed");
		}

		WaitForSingleObject(handle_accept, INFINITE);
	}
	void Server_tcp::Bind(unsigned port)
	{
		localAddr.addr_4 = GetLocalIP(); // no matter ,this value would be changed
		localAddr.port = port;
		BindConfig(localAddr);
	}

	void Server_tcp::BroadCast(std::string s)
	{
		for (int i = 0;i < g_server->conn_list.size();i++)
		{
			g_server->SendByAddr(g_server->conn_list[i].second, s);
		}
	}

	bool Server_tcp::Verify(std::string a, std::string p)
	{
		fstream in;
		in.open(fileName, ios::in);
		if (!in.is_open())
		{
			Error("storage file opened fail.");
			exit(1);
		}
		char buffer[256];
		bool res = false;
		while (!in.eof())
		{
			string s, acn, psw;
			in.getline(buffer, 100);
			s = buffer;
			for (size_t i = 0;i < s.length();++i)
			{
				if (s[i] == ',')
				{
					acn = s.substr(0, i);
					psw = s.substr(i + 1);
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

	void Server_tcp::SendByAddr(std::string addr, std::string s)
	{
		socket_addr saddr;
		saddr.addr_4 = addr;
		saddr.port = localAddr.port;
		SOCKET tmp_conn;
		if (tmp_conn = LookSocketByaddr(addr))
			SendTo(tmp_conn, s);
		else
		{
			Error("Addr didn't exist.");
		}
	}

	void Server_tcp::Register(std::string ac, std::string psw)
	{
		fstream out;
		out.open(fileName, ios::in | ios::out | ios::ate);
		out << ac << "," << psw << endl;
		out.close();
	}

	void Server_tcp::SendLoginTable(std::string addr)
	{
		string msg = "Server: ";
		map<string, string>::iterator it;
		for (it = loginTable.begin();it != loginTable.end();it++)
		{
			msg = msg + (*it).first + " ";
		}
		SendByAddr(addr, msg);
	}

	SOCKET Server_tcp::LookSocketByaddr(string addr)
	{
		for (int i = 0;i < g_server->conn_list.size();i++)
		{
			if (g_server->conn_list[i].second == addr)
				return g_server->conn_list[i].first;
		}
		return NULL;
	}

	Server_tcp::Server_tcp()
	{
		g_server = this;
		serverName = "";
		fileName = "psw.txt";
		Initial();
	}


	Server_tcp::~Server_tcp()
	{
	}

	void Debug_printvec(vector<pair<SOCKET, string> > &t)
	{
		for (size_t i = 0; i < t.size(); i++)
		{
			cout << t[i].first << " " << t[i].second << endl;
		}
	}
}