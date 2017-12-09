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
	class  Telnet_Server_tcp: public Tcp
	{
	public:
		void Run();
		void Bind(unsigned port);
		void BroadCast(std::string s);
		void SendByName(std::string addr, std::string s);
		void SendLoginTable(std::string name);
		SOCKET LookSocketByName(string name);
		string LookNameBySocket(SOCKET s);
		Telnet_Server_tcp();
		~Telnet_Server_tcp();
		std::map<SOCKET, string> loginTable;
		std::vector<pair<SOCKET, string> > conn_list;
		string fileName;
		string serverName;
		socket_addr localAddr;
		socket_addr broadCastAddr;
		socket_addr senderAddr;
		
	};

}