#include "../src/Udp.h"
#include "../src/Tcp.h"
#include "../src/Client.h"
#include "../src/Server.h"
#include "../src/Client_tcp.h"
#include "../src/Server_tcp.h"
#include "../src/RecClient.h"
#include "../src/Telnet_Server_tcp.h"
#include<iostream>
#include <string>
using namespace std;
#define MULTICAST
int main() {
	string s;

	/////////////////
	// udp version

	//cout << "input server ip: " ;
	//cin >> s;
	//TX::Client test(s,5020);
	//test.Run();

	//TX::Server test;
	//test.Bind(5020);
	//test.Run();

	//RecClient test;
	//test.Bind(5020);
	//test.Run();

	///////////////
	// tcp version
	//TX::Server_tcp test;
	//cout << "server ip: "<<test.GetLocalIP() << endl;
	//test.Bind(5020);
	//test.Run();


	//TX::Client_tcp test("127.0.0.1",5020);
	
	//cout << "input server ip: " ;
	//cin >> s;
	//TX::Client_tcp test(s,5020);
	//if(test.Config())
	//	test.Run();


	//////////////
	// telnet versino
	TX::Telnet_Server_tcp test;
	cout << "server ip: " << test.GetLocalIP() << endl;
	test.Bind(5020);
	test.Run();
	cin >> s;
	return 0;
}