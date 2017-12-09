#pragma once


#include<iostream>
#include"Tcp.h"
#include"Error.h"
#include<string>
#include<map>
#include<fstream>

namespace TX
{
	using namespace std;
	class Server_tcp: public Tcp
	{
	public:
		void Run();
		void Bind(unsigned port);
		void BroadCast(std::string s);
		bool Verify(std::string a, std::string p);
		void SendByAddr(std::string addr, std::string s);
		void Register(std::string ac, std::string psw);
		void SendLoginTable(std::string addr);
		SOCKET LookSocketByaddr(string addr);
		Server_tcp();
		~Server_tcp();
		std::vector<std::pair<SOCKET, string> > conn_list;
		std::map<string, string> loginTable;
		string fileName;
		string serverName;
		socket_addr localAddr;
		socket_addr broadCastAddr;
		socket_addr senderAddr;
		
	};

}