// client
#include<Winsock2.h>
#include<stdio.h>
#include<iostream>
#include<string>
#pragma comment(lib,"ws2_32.lib")

//�������˿ں�Ϊ5050
#define DEFAULT_PORT  5020
//����������
#define DATA_BUFFER   1024
using namespace std;

int main()
{
	 WSADATA wsaData;
	 SOCKET sClient;
	 int iPort=DEFAULT_PORT;
	 //��������ַ����
	 int iLen;
	 //�������˵�ַ
	 struct sockaddr_in ser,ser1;
	 if(WSAStartup(MAKEWORD(2,2),&wsaData)!=0)
	 {
		printf("Failed to load Winsock.\n");
		return 0;
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
	 //��ʼ������
	 cout<<"�����÷�������ַ��"<<endl;
	 string serverAddr;
	 cin>>serverAddr;
	 cout << "��������������ı����� "<<endl;
	 string name;
	 cin>>name;
	 ser.sin_family=AF_INET;
	 ser.sin_port=htons(iPort);
	 ser.sin_addr.s_addr=inet_addr(serverAddr.c_str());
	 //�����ͻ������ݱ��׽ӿ�
	 sClient=socket(AF_INET,SOCK_DGRAM,0);
	 if(sClient==INVALID_SOCKET)
	 {
		printf("socket( )Failed:%d\n",WSAGetLastError( ));
		return 0;
	 }
	 iLen=sizeof(ser);
	 //��һ�η��͵�¼��Ϣ
	 string firstSend = name+" login.";
	 int res = sendto(sClient, firstSend.c_str(),firstSend.length(), 0, (struct sockaddr*)&ser, iLen);
	while(1)
	{
        //Ҫ���͸�����������Ϣ
   	    string send_buf;
        printf("send to server:");
		cin >> send_buf;
		if(send_buf[0] == '*')
		{
			string s = "*"+name;
			int res = sendto(sClient, s.c_str(),s.length(),0, (struct sockaddr*)&ser,iLen);
			printf("client close..\n");
			break;
		}
		string s = name+ " : " + send_buf;
		int res = sendto(sClient, s.c_str(),s.length(), 0, (struct sockaddr*)&ser, iLen);
	}
	 closesocket(sClient);
	 WSACleanup( );
	 return 0;
}
