#pragma once
#include "Server.h"
#include "Error.h"
class RecClient:public TX::Server
{
public:
	RecClient();
	void Run();
	~RecClient();
};

