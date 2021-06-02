#pragma once
#include "Sockets.h"

class WinSockInitializer
{
public:	
	static WinSockInitializer* GetInstance();
	~WinSockInitializer();
private:

	WinSockInitializer();
	static WinSockInitializer* winSock;		
};


