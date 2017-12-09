#pragma once
#pragma comment(lib, "ws2_32.lib") 

#include <winsock2.h>  
#include <iostream>
#include "Error.h"
#include "Udp.h"
#include <vector>
namespace TX
{
	using namespace std;

	class Tcp
	{
	public:
		Tcp();
		void Initial();
		void InitialSocket();
		void Cleanup();
		sockaddr_in MakeRawSocketAddr(socket_addr &addr);
		void SendTo(SOCKET& conn, string& str);
		string ReceiveMsg(SOCKET& conn);
		void BindConfig(socket_addr &addr);
		bool AcceptConfig(std::pair<SOCKET, string> *t);
		SOCKET& GetSocket();
		string GetLocalIP();
		~Tcp();
	private:
		SOCKET u_socket;
		WORD wVersionRequested;//create socket's version number
		WSADATA wsaData;

	};

}