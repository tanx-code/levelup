#include "Telnet_Server_tcp.h"

namespace TX
{
	std::wstring c2w(const char *pc);
	std::string w2c(const wchar_t * pw);

	Telnet_Server_tcp* g_server;

	DWORD WINAPI  ThreadHandle_telnet(LPVOID pM);

	// this thread will never quit
	DWORD WINAPI  ThreadAccept_telnet(LPVOID pM)
	{
		 Telnet_Server_tcp* t_server = ( Telnet_Server_tcp *)pM; //no use
		int i = 0;
		std::pair<SOCKET, string>* tmp = new std::pair<SOCKET, string>;
		while (i < 10)
		{
			if (g_server->AcceptConfig(tmp))
			{

				g_server->conn_list.push_back(*tmp);
				g_server->loginTable[tmp->first] = tmp->second;
				++i;
				HANDLE handle_obj = CreateThread(NULL, 0, ThreadHandle_telnet, (LPVOID)(tmp->first), 0, NULL);
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

	DWORD WINAPI  ThreadHandle_telnet(LPVOID pM)
	{

		Error("gennered a thread: ");
		SOCKET conn = (SOCKET)pM;

		string recv = "";
		while (1)
		{
			recv = g_server->ReceiveMsg(conn);

			if (recv != "")
			{
				if (recv.substr(0,6) == "chname")
				{  
					if (g_server->LookSocketByName(recv.substr(7)) != NULL)
					{
						ConsoleMsg("server: this name already exist!");
						break;
					}
					string msg = g_server->LookNameBySocket(conn) + " change his name to " + recv.substr(7);
					ConsoleMsg("server: " + msg);
					g_server->loginTable[conn] = recv.substr(7);
					g_server->BroadCast(msg); 
					recv = ""; 
					continue;
				}
				if (recv.substr(0, 5) == "query")
				{
					g_server->SendLoginTable(g_server->loginTable[conn]);
					recv = "";
					continue;
				}
				ConsoleMsg(g_server->loginTable[conn] + " say: " + recv);
				g_server->BroadCast(g_server->loginTable[conn] + " say: " + recv);
				recv = "";
			}
			else 
				break;
		}
		Error("Exit a thread: "+g_server->loginTable[conn]);
		g_server->loginTable.erase(conn);
		g_server->BroadCast("Server: " + g_server->loginTable[conn] + " logout !");
		return 0;
	}
	void  Telnet_Server_tcp::Run()
	{
		cout << "Server start" << endl;
		// creat accept loop thread
		HANDLE handle_accept = CreateThread(NULL, 0, ThreadAccept_telnet, (LPVOID)this, 0, NULL);
		if (handle_accept == NULL)
		{
			Error("creat thread failed");
		}

		WaitForSingleObject(handle_accept, INFINITE);
	}
	void  Telnet_Server_tcp::Bind(unsigned port)
	{
		localAddr.addr_4 = GetLocalIP(); // no matter ,this value would be changed
		localAddr.port = port;
		BindConfig(localAddr);
	}

	void  Telnet_Server_tcp::BroadCast(std::string s)
	{
		map<SOCKET, string>::iterator it;
		for (it = loginTable.begin();it != loginTable.end();it++)
		{
			SendByName((*it).second, s);
		}
	}

	void  Telnet_Server_tcp::SendByName(std::string name, std::string s)
	{
		SOCKET tmp_conn;
		if (tmp_conn = LookSocketByName(name))
			SendTo(tmp_conn, s);
		else
		{
			Error("Socket didn't exist.");
		}
	}

	void  Telnet_Server_tcp::SendLoginTable(std::string name)
	{
		string msg = "Server: ";
		map<SOCKET, string>::iterator it;
		for (it = loginTable.begin();it != loginTable.end();it++)
		{
			msg = msg + (*it).second + " ";
		}
		SendByName(name, msg);
	}

	SOCKET  Telnet_Server_tcp::LookSocketByName(string name)
	{
		map<SOCKET, string>::iterator it;
		for (it = loginTable.begin();it != loginTable.end();it++)
		{
			if ((*it).second == name)
				return (*it).first;
		}
		return NULL;
	}

	string Telnet_Server_tcp::LookNameBySocket(SOCKET s)
	{
		map<SOCKET, string>::iterator it;
		for (it = loginTable.begin();it != loginTable.end();it++)
		{
			if ((*it).first == s)
				return (*it).second;
		}
		return string();
	}

	 Telnet_Server_tcp:: Telnet_Server_tcp()
	{
		g_server = this;
		serverName = "";
		fileName = "psw.txt";
		Initial();
	}


	 Telnet_Server_tcp::~ Telnet_Server_tcp()
	{
	}


}