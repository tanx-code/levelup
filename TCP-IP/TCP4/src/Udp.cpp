#include "Udp.h"

namespace TX {

	Udp::Udp()
	{
	}

	void Udp::Initial()
	{
		wVersionRequested = MAKEWORD(2, 2);
		InitialSocket();
	}

	void Udp::InitialSocket() {
		int err = WSAStartup(wVersionRequested, &wsaData);
		if (err != 0)
		{
			Error("Socket initial fail£¬Exit!");
		}

		u_socket = socket(AF_INET, SOCK_DGRAM, 0);
		if (u_socket == INVALID_SOCKET) {
			Error("Socket create fail£¬Exit!");
		}

	}

	sockaddr_in Udp::MakeRawSocketAddr(socket_addr &addr){
		sockaddr_in rawaddr;
		rawaddr.sin_family = AF_INET;
		rawaddr.sin_addr.s_addr = inet_addr(addr.addr_4.c_str());
		rawaddr.sin_port = htons(addr.port);
		return rawaddr;
	}

	void Udp::SendTo(socket_addr &addr,std::string& str) {
		sockaddr_in saddr = MakeRawSocketAddr(addr);
		int nlen = sizeof(saddr);
		int res = sendto(u_socket, str.c_str(), str.length(), 0, (sockaddr*)&saddr, nlen);
		if (res == SOCKET_ERROR) {
			Error("Send fail");
		}
	}

	std::string Udp::ReceiveMsg() {
		char buf[1024] = "";
		struct sockaddr_in	cli;
		int iLen = sizeof(cli);
		int iRecv = recvfrom(u_socket, buf, sizeof(buf), 0, (SOCKADDR*)&cli, &iLen);
		if (iRecv == SOCKET_ERROR|| iRecv == 0) {
			Error("receive fail");
			return "";
		}
		return std::string(buf);
	}

	void Udp::BindConfig(socket_addr & addr)
	{
		sockaddr_in myaddr = MakeRawSocketAddr(addr);
		myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
		if (bind(u_socket, (sockaddr*)&myaddr, sizeof(myaddr)) == SOCKET_ERROR) {
			ERROR("bind fail");
			return;
		}
	}

	SOCKET & Udp::GetSocket()
	{
		return u_socket;
	}

	std::string Udp::GetLocalIP()
	{
		char szHost[256];
		gethostname(szHost, 256);
		hostent *pHost = gethostbyname(szHost);
		in_addr addr;
		char *p = pHost->h_addr_list[0];
		memcpy(&addr.S_un.S_addr, p, pHost->h_length);
		char *szIp = inet_ntoa(addr);
		std::string ipaddr = szIp;
		return ipaddr;
	}

	void Udp::Cleanup() {
		if (!closesocket(u_socket))
		{
			WSAGetLastError();
			return;
		}
		if (!WSACleanup())
		{
			WSAGetLastError();
			return;
		}
	}

	Udp::~Udp()
	{
	}

}