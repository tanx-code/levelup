//server
#include<Winsock2.h>
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string>
#pragma comment(lib,"ws2_32.lib")
//服务器端口号为5020
#define DEFAULT_PORT  5020
//接收数据缓冲区长度
#define BUFFER_LENGTH  1024
using namespace std;
void main()
{
	int so_broadcast = 1;
	int iPort = DEFAULT_PORT;
	WSADATA wsaData;
	SOCKET	sSocket,cli1Socket,cli2Socket;
	//客户地址长度
	int iLen;
	//发送的数据长度
	int iSend;
	//接收的数据长度
	int iRecv;
	//要发送给客户的信息
	char send_buf[] = "Hello! I am a server.";
	//接收数据的缓冲区
	char recv_buf[BUFFER_LENGTH];
	//本地地址和客户地址
	struct sockaddr_in	ser, cli, my_addr;
	printf("-------------------------------\n");
	printf("Server waiting\n");
	printf("-------------------------------\n");
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		printf("Failed to load Winsock.\n ");
		return;
	}
	//产生服务器端套接口
	int iLen1 = 0;int iLen2 = 0;
	sSocket = socket(AF_INET, SOCK_DGRAM, 0);
	if (sSocket == INVALID_SOCKET)
	{
		printf("socket( ) Failed: %d\n", WSAGetLastError());
		return;
	}
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(iPort);
	my_addr.sin_addr.s_addr = inet_addr("255.255.255.255");
	//以下建立服务器端地址
	ser.sin_family = AF_INET;
	ser.sin_port = htons(iPort);
	ser.sin_addr.s_addr = htonl(INADDR_ANY);
	//广播
	setsockopt(sSocket, SOL_SOCKET, SO_BROADCAST, (const char*)&so_broadcast, sizeof(int));
	if (bind(sSocket, (LPSOCKADDR)&ser, sizeof(ser)) == SOCKET_ERROR)
	{
		printf("bind( ) Failed: %d\n", WSAGetLastError());
		return;
	}
	sendto(sSocket, send_buf, sizeof(send_buf), 0, (struct sockaddr *)&my_addr, sizeof(my_addr));
	int size = sizeof(ser);
	recvfrom(sSocket, recv_buf, BUFFER_LENGTH, 0, (struct sockaddr *)&ser, &size);
	cout << recv_buf<<endl;
	memset(recv_buf, 0, sizeof(recv_buf));
	////进入一个无限循环，进行数据接收和发送
	while (true)
	{
		//从客户端接收数据
		iRecv = recvfrom(sSocket, recv_buf, BUFFER_LENGTH, 0, (SOCKADDR*)&ser, &size);
		if (iRecv == SOCKET_ERROR)
		{
			printf("recvfrom( ) Failed.:%d\n", WSAGetLastError());
			break;
		}
		if (iRecv == 0)
			break;
		if (recv_buf[0] == '*')
		{
			cout << recv_buf<<endl;
			string s =recv_buf;
			s = s.substr(1);
			cout << s <<"  logout."<< endl;
			iSend = sendto(sSocket, recv_buf, sizeof(recv_buf), 0, (struct sockaddr *)&my_addr, sizeof(my_addr));
			//清空recv_buf缓存
			recvfrom(sSocket, recv_buf, BUFFER_LENGTH, 0, (SOCKADDR*)&ser, &size);
			memset(recv_buf, 0, sizeof(recv_buf));
		}else{
				cout<< recv_buf<<endl;
				iSend = sendto(sSocket, recv_buf, sizeof(recv_buf), 0, (struct sockaddr *)&my_addr, sizeof(my_addr));
				if (iSend == SOCKET_ERROR ) {
					printf("failed \n");
					break;
				}
				if (iSend == 0 ) {
					printf("failed \n");
					break;
				}
				printf("send good!\n");
				//清空recv_buf缓存
				recvfrom(sSocket, recv_buf, BUFFER_LENGTH, 0, (SOCKADDR*)&ser, &size);
				memset(recv_buf, 0, sizeof(recv_buf));
		 }
	}
	closesocket(sSocket);
	WSACleanup();
}
