#include "Client.h"

namespace TX {

	Client::Client(std::string addr, unsigned port)
	{
		targetAddr.addr_4 = addr;
		targetAddr.port = port;
		clientName = "default";
		Initial();
	}

	void Client::Login()
	{
		std::string name, psw, ip, target;
		ip = GetLocalIP();
		ConsoleMsg("User name:");
		std::cin >> name;
		ConsoleMsg("Password:");
		std::cin >> psw;
		Send("L"+ip+":"+name+","+psw);

		ConsoleMsg("====================");
		ConsoleMsg("go on");
		ConsoleMsg("====================");
		ConsoleMsg("1.Public chat");
		ConsoleMsg("2.Personal chat");
		ConsoleMsg("3.Online people");
		ConsoleMsg("4.Quit");
		ConsoleMsg("");

		int i=0;
		while (1) {
			std::cout<<"wait> ";
			std::cin >> i;
			if (i == 1)
			{
				std::string msg = "";
				while (msg != "exit") {
					std::cout << "public> ";
					std::cin >> msg;
					if (msg == "exit") {
						break;
					}
					Send("M0" + name + ":" + msg);
				}
			}
			if (i == 2)
			{
				std::string msg = "";
				while (msg != "exit") {
					std::cout << "personal> ";
					std::cin >> target ;
					if (target == "exit") {
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

	void Client::Register()
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

	void Client::Send(std::string s)
	{
		SendTo(targetAddr, s);
	}

	void Client::Config() {

	}

	void Client::Run() {
		while (1) {
			ConsoleMsg("====================");
			ConsoleMsg("Welcome to ChatRoom.");
			ConsoleMsg("====================");
			ConsoleMsg("1.Login");
			ConsoleMsg("2.Register");
			ConsoleMsg("3.Exit");
			ConsoleMsg("");

			std::cout << "wait> ";
			int i;
			std::cin >> i;
			if (i == 1)
				Login();
			if (i == 2)
				Register();
			if (i == 3)
				exit(1);
		}

	}

	Client::~Client()
	{
	}

}