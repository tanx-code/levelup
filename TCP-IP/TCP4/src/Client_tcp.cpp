#include "Client_tcp.h"

namespace TX
{
	CRITICAL_SECTION g_CS;
	Client_tcp* g_client;
	DWORD WINAPI  ThreadSend(LPVOID pM);
	DWORD WINAPI  ThreadRecv(LPVOID pM);
	void Client_tcp::Login()
	{
		std::string name, psw, ip, target;
		ip = GetLocalIP();
		ip = "127.0.0.1";
		ConsoleMsg("User name:");
		std::cin >> name;
		ConsoleMsg("Password:");
		std::cin >> psw;
		Send("L" + ip + ":" + name + "," + psw);

		ConsoleMsg("====================");
		ConsoleMsg("go on");
		ConsoleMsg("====================");
		ConsoleMsg("1.Public chat");
		ConsoleMsg("2.Personal chat");
		ConsoleMsg("3.Online people");
		ConsoleMsg("4.Quit");
		ConsoleMsg("");

		int i = 0;
		while (1)
		{
			std::cout << "wait> ";
			std::cin >> i;
			if (i == 1)
			{
				std::string msg = "";
				while (msg != "exit")
				{
					std::cout << "public> ";
					std::cin >> msg;
					if (msg == "exit")
					{
						break;
					}
					Send("M0" + name + ":" + msg);
				}
			}
			if (i == 2)
			{
				std::string msg = "";
				while (msg != "exit")
				{
					std::cout << "personal> ";
					std::cin >> target;
					if (target == "exit")
					{
						break;
					}
					std::cin >> msg;
					Send("M1" + target + ":" + name + ":" + msg);
				}
			}
			if (i == 3)
			{
				Send("Q" + ip);
			}
			if (i == 4)
			{
				Send("*" + ip + ":" + name);
				break;
			}
		}
	}
	void Client_tcp::Register()
	{
		std::string name, psw, ip;
		ConsoleMsg("Register .");
		ip = GetLocalIP();
		ConsoleMsg("User name:");
		std::cin >> name;
		ConsoleMsg("Password:");
		std::cin >> psw;
		Send("R" + ip + ":" + name + "," + psw);
	}
	void Client_tcp::Send(std::string s)
	{
		SendTo(GetSocket(),s);
	}
	bool Client_tcp::Config()
	{
		int ret = 0;
		sockaddr_in t_addr = MakeRawSocketAddr(targetAddr);
		ret = connect(GetSocket(), (struct sockaddr*)&t_addr, sizeof(t_addr));
		if (ret != 0)
		{
			Error("connect failed");
			return false;
		}
		else
		{
			Error("连接成功");
			return true;
		}
	}
	DWORD WINAPI  ThreadSend(LPVOID pM)
	{
		ConsoleMsg("Send thread start");
		while (1)
		{
			EnterCriticalSection(&g_CS);
			ConsoleMsg("====================");
			ConsoleMsg("Welcome to ChatRoom.");
			ConsoleMsg("====================");
			ConsoleMsg("1.Login");
			ConsoleMsg("2.Register");
			ConsoleMsg("3.Exit");
			ConsoleMsg("");
			LeaveCriticalSection(&g_CS);
			std::cout << "wait> ";
			int i;
			std::cin >> i;
			if (i == 1)
				g_client->Login();
			if (i == 2)
				g_client->Register();
			if (i == 3)
				exit(1);
		}
	}
	DWORD WINAPI  ThreadRecv(LPVOID pM)
	{
		ConsoleMsg("Recv thread start");
		bool conn = false;
		while (1)
		{
			std::string s = g_client->ReceiveMsg(g_client->GetSocket());
			if (s.substr(0, 6) == "Server")
			{
				EnterCriticalSection(&g_CS);
				ConsoleMsg("\n");
				ConsoleMsg(s);
				LeaveCriticalSection(&g_CS);
			}
			if (s == "Login200")
				conn = true;
			if (conn)
			{
				while (1)
				{
					std::string msg = g_client->ReceiveMsg(g_client->GetSocket());
					if (msg[0] == '*')
					{
						std::string ip, account;
						for (size_t i = 1;i < msg.length();++i)
						{
							if (msg[i] == ':')
							{
								ip = msg.substr(1, i - 1);
								account = msg.substr(i + 1);
								break;
							}
						}
						if (ip == g_client->GetLocalIP())
						{
							conn = false;
							EnterCriticalSection(&g_CS);
							ConsoleMsg("\n");
							ConsoleMsg(account + " logout.");
							LeaveCriticalSection(&g_CS);
							break;
						}
						EnterCriticalSection(&g_CS);
						ConsoleMsg("\n");
						ConsoleMsg(account + " logout.");
						LeaveCriticalSection(&g_CS);
						continue;
					}
					EnterCriticalSection(&g_CS);
					ConsoleMsg("\n");
					ConsoleMsg(msg);
					LeaveCriticalSection(&g_CS);
				}
			}
		}
	}
	void Client_tcp::Run()
	{

		HANDLE handle_send = CreateThread(NULL, 0, ThreadSend, (LPVOID)this, 0, NULL);
		HANDLE handle_recv = CreateThread(NULL, 0, ThreadRecv, (LPVOID)this, 0, NULL);
		//WaitForSingleObject(handle_send, INFINITE);
		WaitForSingleObject(handle_recv, INFINITE);
	}
	Client_tcp::Client_tcp(string addr, unsigned port)
	{
		targetAddr.addr_4 = addr;
		targetAddr.port = port;
		clientName = "default";
		g_client = this;
		InitializeCriticalSection(&g_CS);
		Initial();
	}
	Client_tcp::~Client_tcp()
	{
	}
}