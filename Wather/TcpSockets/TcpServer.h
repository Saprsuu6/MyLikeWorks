#pragma once

class EXPORT TcpServer
{
public:

	TcpServer();
	~TcpServer();

	void GetAddresInfo();
	void ConnectionWithWatherServer();
	string MakingMassage(const string& town);
	void FindWather(const string& massage);
	string GetAnswer();
	void bind(string ipAddress, unsigned short port);
	void listen();
	TcpClient* accept();
	
private:
	SOCKET _listenSocket;
	addrinfo* result = NULL;
	addrinfo hints;
	SOCKET connectSocket = INVALID_SOCKET;
	addrinfo* ptr = NULL;
	char hostname[255] = "api.openweathermap.org";
	int iResult = 0;
};

