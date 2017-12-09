/**********************************************
*
* ModuleName：	Udp
* Description：	对udp通信的低级封装
* Author:   	arctanx
*
**********************************************/
#pragma once
#pragma comment(lib, "ws2_32.lib") 


#include <winsock2.h>  
#include <iostream>
#include "Error.h"
namespace TX {
	struct socket_addr {
		std::string addr_4;
		unsigned port;
	};
	class Udp
	{
	public:
		Udp();
		void Initial();
		void InitialSocket();
		void Cleanup();
		sockaddr_in MakeRawSocketAddr(socket_addr &addr);
		void SendTo(socket_addr &addr, std::string& str);
		std::string ReceiveMsg();
		void BindConfig(socket_addr &addr);
		SOCKET& GetSocket();
		std::string GetLocalIP();
		virtual ~Udp();

	private:
		SOCKET u_socket;
		WORD wVersionRequested;//create socket's version number
		WSADATA wsaData;
	};

}
