#pragma once

#include <iostream>
#include<string>
#include "Udp.h"
#include "Error.h"

namespace TX {

	class Client : public Udp
	{
	public:
		Client(std::string addr, unsigned port);
		void Login();
		void Register();
		void Send(std::string s);
		void Config();
		void Run();
		~Client();
	private:
		std::string clientName;
		socket_addr targetAddr;
	};

}