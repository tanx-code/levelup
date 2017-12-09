//server
#include<Winsock2.h>
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string>
#pragma comment(lib,"ws2_32.lib")
//�������˿ں�Ϊ5020
#define DEFAULT_PORT  5020
//�������ݻ���������
#define BUFFER_LENGTH  1024
using namespace std;
void main()
{
	int so_broadcast = 1;
	int iPort = DEFAULT_PORT;
	WSADATA wsaData;
	SOCKET	sSocket,cli1Socket,cli2Socket;
	//�ͻ���ַ����
	int iLen;
	//���͵����ݳ���
	int iSend;
	//���յ����ݳ���
	int iRecv;
	//Ҫ���͸��ͻ�����Ϣ
	char send_buf[] = "Hello! I am a server.";
	//�������ݵĻ�����
	char recv_buf[BUFFER_LENGTH];
	//���ص�ַ�Ϳͻ���ַ
	struct sockaddr_in	ser, cli, my_addr;
	printf("-------------------------------\n");
	printf("Server waiting\n");
	printf("-------------------------------\n");
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		printf("Failed to load Winsock.\n ");
		return;
	}
	//�������������׽ӿ�
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
	//���½����������˵�ַ
	ser.sin_family = AF_INET;
	ser.sin_port = htons(iPort);
	ser.sin_addr.s_addr = htonl(INADDR_ANY);
	//�㲥
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
	////����һ������ѭ�����������ݽ��պͷ���
	while (true)
	{
		//�ӿͻ��˽�������
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
			//���recv_buf����
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
				//���recv_buf����
				recvfrom(sSocket, recv_buf, BUFFER_LENGTH, 0, (SOCKADDR*)&ser, &size);
				memset(recv_buf, 0, sizeof(recv_buf));
		 }
	}
	closesocket(sSocket);
	WSACleanup();
}
