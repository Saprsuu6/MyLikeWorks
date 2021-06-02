#pragma once
#include "Header.h"

class EXPORT TcpClient
{
public:

	TcpClient();
	TcpClient(SOCKET socket);

	TcpClient(const TcpClient& tcpClient) = delete;
	TcpClient operator=(const TcpClient& tcpClient) = delete;
	
	TcpClient(TcpClient&& tcpClient);
	void operator=(TcpClient&& tcpClient);

	~TcpClient();

	void connect(string ipAddress, unsigned short port);

	string receive();
	void send(string data);

	void shutdown();

	const SOCKET* GetSocket() const;
	void SetSocket(const SOCKET& soket);

private:
	SOCKET _clientSocket;
	char _recvbuf[1024];
};

