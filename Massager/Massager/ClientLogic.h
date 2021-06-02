#pragma once
#include "Header.h"
class ClientLogic
{
private:
	TcpClient client;
	string name;
public:
	void SendMassage(string& str);
	void Logic(Windows& window, MyStruct& strct);

	const TcpClient* GetTcpClient() const;
};

inline const TcpClient* ClientLogic::GetTcpClient() const
{
	return &client;
}

inline void ClientLogic::SendMassage(string& str)
{
	client.send(str);
}

DWORD WINAPI Getting(LPVOID lp) {
	MyStruct* strct = (struct MyStruct*)lp;

	while (true) {
		string response = strct->client.receive();

		if (strstr(response.c_str(), "<CHNG>") != NULL) {
			response.replace(response.find("<CHNG>"), 6, "");
			strct->window->AddToListBox(response);
		}

		else if (strstr(response.c_str(), "<TEXT>") != NULL) {
			response.replace(response.find("<TEXT>"), 6, "");
			strct->window->AddToChat(response);
		}
	}

	return 0;
}

void ClientLogic::Logic(Windows& window, MyStruct& strct)
{
	try {
		client.connect("127.0.0.1", 1111);
		strct.client.SetSocket(*client.GetSocket());

		HANDLE Reporting = CreateThread(0, 0, Getting, (LPVOID)&strct, 0, 0);
	}
	catch (SocketException& ex) {
		cout << ex.what() << endl;
		client.shutdown();
	}
}

