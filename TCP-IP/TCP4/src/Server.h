/**********************************************
*
* ModuleName：	基于UDP的聊天服务器
* Description：	自己设计的一套简单的交互协议:
				exit                protocol: [*(IP):(ACCOUNT)]
				login               protocol: [L(IP):(ACOUNT),(PASSWORD)]
				register	        protocol: [R(IP):(ACOUNT),(PASSWORD)]
				chat msg	        protocol: [M0(MSG)] || [M1(ACOUNT):(MSG)]
				query logintable    protocol: [Q(IP)]

* Author:   	arctanx
*
**********************************************/
#pragma once
#include<iostream>
#include"Udp.h"
#include"Error.h"
#include<string>
#include<map>
#include<fstream>


namespace TX {

	class Server: public Udp
	{
	public:
		Server();
		virtual ~Server();
		void Bind(unsigned port);
		void BroadCast(std::string s);
		void Run();
		bool Verify(std::string a, std::string p);
		void SendByAddr(std::string addr, std::string s);
		void Register(std::string ac, std::string psw);
		void SendLoginTable(std::string addr);

	private:
		std::string fileName;
		std::string serverName;
		socket_addr localAddr;
		socket_addr broadCastAddr;
		socket_addr senderAddr;
		std::map<std::string, std::string> loginTable;
	};
}
