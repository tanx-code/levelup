#include "RecClient.h"



RecClient::RecClient()
{

}

void RecClient::Run()
{
	Bind(5020);
	bool conn = false;
	ConsoleMsg("Local server start.");
	while (1) {
		std::string s = ReceiveMsg();
		if (s.substr(0,6)=="Server") {
			ConsoleMsg(s);
		}
		if (s == "Login200")
			conn = true;
		if (conn) {
			while (1) {
				std::string msg = ReceiveMsg();
				if (msg[0] == '*') {
					std::string ip, account;
					for (size_t i = 1;i < msg.length();++i) {
						if (msg[i] == ':') {
							ip = msg.substr(1, i - 1);
							account = msg.substr(i + 1);
							break;
						}
					}
					if (ip == GetLocalIP()) {
						conn = false;
						ConsoleMsg(account + " logout.");
						break;
					}
					ConsoleMsg(account+" logout.");
					continue;
				}
				ConsoleMsg(msg);
			}
		}
	}
}

RecClient::~RecClient()
{
}
