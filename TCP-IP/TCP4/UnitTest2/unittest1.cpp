#include "stdafx.h"
#include "CppUnitTest.h"
#include <CppUnitTestAssert.h>
#include"../src/Udp.h"
#include"../src/Client.h"
#include"../src/Server.h"
#include<string>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace UnitTest2
{		

	TEST_CLASS(SERVER_CLASS)
	{
	public:

		TEST_METHOD(GetlocalIpTest)
		{
			TX::Client test("172.17.194.95", 5020);
			std::string ip = test.GetLocalIP();
			Assert::AreEqual(std::string("172.17.194.95"),ip);
		}

		TEST_METHOD(Send0Test) 
		{
			TX::Client test("172.17.194.107", 5020);
			std::string ip = test.GetLocalIP();
			test.Send("M0tanxiao:nihao");
		}
		TEST_METHOD(Send1Test)
		{
			TX::Client test("172.17.194.95", 5020);
			std::string ip = test.GetLocalIP();
			test.Send("M1172.17.194.95:tanxiao:preson");
		}
		TEST_METHOD(LoginTest)
		{
			TX::Client test("172.17.194.95", 5020);
			std::string ip = test.GetLocalIP();
			test.Send("L172.17.194.95:tanxiao,123456");
		}
		TEST_METHOD(RegisterTest)
		{
			TX::Client test("172.17.194.95", 5020);
			std::string ip = test.GetLocalIP();
			test.Send("R172.17.194.95:tanxiao,123456");
		}
		TEST_METHOD(QueryTest)
		{
			TX::Client test("172.17.194.95", 5020);
			std::string ip = test.GetLocalIP();
			test.Send("Q172.17.194.95");
		}
		TEST_METHOD(ExitTest)

		{
			TX::Client test("172.17.194.95", 5020);
			std::string ip = test.GetLocalIP();
			test.Send("*172.17.194.95:tanxiao");
		}
		TEST_METHOD(SClientTest)

		{
			TX::Client test("172.17.194.95", 5020);
			std::string ip = test.GetLocalIP();
			test.Send("Login200");
			test.Send("*172.17.194.94:others");
			test.Send("jj:nihao");
			test.Send("*172.17.194.95:tanxiao");
			test.Send("*172.17.194.94:others");
			test.Send("jj:nihao");
		}
	};
}