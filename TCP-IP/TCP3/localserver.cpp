//server
#include<Winsock2.h>
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string>

//服务器端口号为5020
#define DEFAULT_PORT  5020
//接收数据缓冲区长度
#define BUFFER_LENGTH  1024
using namespace std;

void main(int argc, char *argv[])
{
	int iPort = DEFAULT_PORT;
	WSADATA wsaData;
	SOCKET	sSocket;
	//客户地址长度
	int iLen;
	//接收的数据长度
	int iRecv;
	//接收数据的缓冲区
	char recv_buf[BUFFER_LENGTH];
	//本地地址和客户地址
	struct sockaddr_in	ser, cli;
	cout << "请输入用于聊天的别名： "<<endl;
	string name;
	cin>>name;
	printf("-------------------------------\n");
	printf("Server waiting\n");
	printf("-------------------------------\n");
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		printf("Failed to load Winsock.\n ");
		return;
	}
	sSocket = socket(AF_INET, SOCK_DGRAM, 0);
	if (sSocket == INVALID_SOCKET)
	{
		printf("socket( ) Failed: %d\n", WSAGetLastError());
		return;
	}
	//以下建立服务器端地址
	ser.sin_family = AF_INET;
	//htons( )函数把一个双字节主机字节顺序的数转换为网络字节顺序的数
	ser.sin_port = htons(iPort);
	//htonl( )函数把一个主机字节顺序的数转换为网络字节顺序的数
	ser.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sSocket, (LPSOCKADDR)&ser, sizeof(ser)) == SOCKET_ERROR)
	{
		printf("bind( ) Failed: %d\n", WSAGetLastError());
		return;
	}
	//获得本地ip地址
    char szHost[256];
	gethostname(szHost, 256);
	hostent *pHost = gethostbyname(szHost);
	in_addr addr;
	char *p = pHost->h_addr_list[0];
    memcpy(&addr.S_un.S_addr, p, pHost->h_length);
	char *szIp = inet_ntoa(addr);
	string ipaddr = szIp;
	cout << ipaddr <<endl;

	iLen = sizeof(cli);
	//初始化接收缓冲区
	memset(recv_buf, 0, sizeof(recv_buf));
	//进入一个无限循环，进行数据接收和发送
	while (true)
	{
		//从客户端接收数据
		iRecv = recvfrom(sSocket, recv_buf, BUFFER_LENGTH, 0, (SOCKADDR*)&cli, &iLen);
		if (iRecv == SOCKET_ERROR)
		{
			printf("recvfrom( ) Failed.:%d\n", WSAGetLastError());
			break;
		}
		if (iRecv == 0)
			break;
		if (recv_buf[0] == '*')
	   {
			string recv_str = recv_buf;
			if (name == recv_str.substr(1)) {
				cout << "server exit" << endl;
				break;
			}
		}
		cout << recv_buf << endl;
		memset(recv_buf, 0, sizeof(recv_buf));
	}
	closesocket(sSocket);
	WSACleanup();
}
