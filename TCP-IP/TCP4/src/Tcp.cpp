#include "Tcp.h"

namespace TX
{
	std::wstring c2w(const char *pc);
	std::string w2c(const wchar_t * pw);

	Tcp::Tcp()
	{
	}


	Tcp::~Tcp()
	{
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
	void Tcp::Initial()
	{
		wVersionRequested = MAKEWORD(2, 2);
		InitialSocket();
	}
	void Tcp::InitialSocket()
	{
		int err = WSAStartup(wVersionRequested, &wsaData);
		if (err != 0)
		{
			Error("Socket initial fail，Exit!");
		}

		u_socket = socket(AF_INET, SOCK_STREAM, 0);
		if (u_socket == INVALID_SOCKET)
		{
			Error("Socket create fail，Exit!");
		}

	}
	void Tcp::Cleanup()
	{
	}
	sockaddr_in Tcp::MakeRawSocketAddr(socket_addr& addr)
	{
		sockaddr_in rawaddr;
		rawaddr.sin_family = AF_INET; // ipv4
		rawaddr.sin_addr.s_addr = inet_addr(addr.addr_4.c_str());
		rawaddr.sin_port = htons(addr.port);
		memset(rawaddr.sin_zero, 0x00, 8);

		return rawaddr;
	}
	void Tcp::SendTo(SOCKET& conn, std::string & str)
	{
		wstring ws = c2w(str.c_str());
		string ss = w2c(ws.c_str());
		int res = send(conn, ss.c_str(), str.length(), 0);
		if (res == SOCKET_ERROR)
		{
			Error("Send fail");
		}
	}
	std::string Tcp::ReceiveMsg(SOCKET& conn)
	{
		char buf[1024] = "";
		int iRecv = recv(conn, buf, sizeof(buf), 0);
		if (iRecv == SOCKET_ERROR || iRecv == 0)
		{
			Error("receive fail");
			return "";
		}
		wstring ws = c2w(buf);
		string ss = w2c(ws.c_str());
		return ss;
	}
	void Tcp::BindConfig(socket_addr & addr)
	{
		sockaddr_in myaddr = MakeRawSocketAddr(addr);
		myaddr.sin_addr.s_addr = INADDR_ANY;
		if (bind(u_socket, (sockaddr*)&myaddr, sizeof(myaddr)) == SOCKET_ERROR)
		{
			Error("bind fail");
			return;
		}
		if (SOCKET_ERROR == listen(u_socket, 5))
		{
			Error("listen() Failed ");
			closesocket(u_socket);
			WSACleanup();
			return;
		}
	}

	bool Tcp::AcceptConfig(std::pair<SOCKET, string> *t)
	{
		sockaddr_in ClientAddr;
		int AddrLen = sizeof(ClientAddr);
		SOCKET sockConnected = accept(u_socket, (sockaddr*)&ClientAddr, &AddrLen);
		if (INVALID_SOCKET == sockConnected)
		{
			Error("accpet() Failed ");
			closesocket(u_socket);
			WSACleanup();
			return false;
		}
		t->first = sockConnected;
		t->second = string(inet_ntoa(ClientAddr.sin_addr));
		printf("%d , %s",t->first,t->second.c_str());
		return true;
	}

	SOCKET & Tcp::GetSocket()
	{
		return u_socket;
	}

	std::string Tcp::GetLocalIP()
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

	std::wstring c2w(const char *pc)
	{
		std::wstring val = L"";

		if (NULL == pc)
		{
			return val;
		}
		//size_t size_of_ch = strlen(pc)*sizeof(char);
		//size_t size_of_wc = get_wchar_size(pc);
		size_t size_of_wc;
		size_t destlen = mbstowcs(0, pc, 0);
		if (destlen == (size_t)(-1))
		{
			return val;
		}
		size_of_wc = destlen + 1;
		wchar_t * pw = new wchar_t[size_of_wc];
		mbstowcs(pw, pc, size_of_wc);
		val = pw;
		delete pw;
		return val;
	}
	std::string w2c(const wchar_t * pw)
	{
		std::string val = "";
		if (!pw)
		{
			return val;
		}
		size_t size = wcslen(pw)*sizeof(wchar_t);
		char *pc = NULL;
		if (!(pc = (char*)malloc(size)))
		{
			return val;
		}
		size_t destlen = wcstombs(pc, pw, size);
		/*转换不为空时，返回值为-1。如果为空，返回值0*/
		if (destlen == (size_t)(0))
		{
			return val;
		}
		val = pc;
		delete pc;
		return val;
	}
}