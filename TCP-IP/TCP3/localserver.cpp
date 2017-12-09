//server
#include<Winsock2.h>
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string>

//�������˿ں�Ϊ5020
#define DEFAULT_PORT  5020
//�������ݻ���������
#define BUFFER_LENGTH  1024
using namespace std;

void main(int argc, char *argv[])
{
	int iPort = DEFAULT_PORT;
	WSADATA wsaData;
	SOCKET	sSocket;
	//�ͻ���ַ����
	int iLen;
	//���յ����ݳ���
	int iRecv;
	//�������ݵĻ�����
	char recv_buf[BUFFER_LENGTH];
	//���ص�ַ�Ϳͻ���ַ
	struct sockaddr_in	ser, cli;
	cout << "��������������ı����� "<<endl;
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
	//���½����������˵�ַ
	ser.sin_family = AF_INET;
	//htons( )������һ��˫�ֽ������ֽ�˳�����ת��Ϊ�����ֽ�˳�����
	ser.sin_port = htons(iPort);
	//htonl( )������һ�������ֽ�˳�����ת��Ϊ�����ֽ�˳�����
	ser.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sSocket, (LPSOCKADDR)&ser, sizeof(ser)) == SOCKET_ERROR)
	{
		printf("bind( ) Failed: %d\n", WSAGetLastError());
		return;
	}
	//��ñ���ip��ַ
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
	//��ʼ�����ջ�����
	memset(recv_buf, 0, sizeof(recv_buf));
	//����һ������ѭ�����������ݽ��պͷ���
	while (true)
	{
		//�ӿͻ��˽�������
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
