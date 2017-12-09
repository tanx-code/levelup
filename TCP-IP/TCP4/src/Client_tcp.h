#pragma once
#include <iostream>
#include<string>
#include "Tcp.h"
#include "Error.h"

namespace TX
{
	class Client_tcp:public Tcp
	{
	public:
		void Login();
		void Register();
		void Send(std::string s);
		bool Config();
		void Run();
		Client_tcp(string addr, unsigned port);
		~Client_tcp();
		string clientName;
		socket_addr targetAddr;
	};

}