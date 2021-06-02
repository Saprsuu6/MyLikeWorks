#pragma once
#include "Header.h"
class ClientLogic
{
private:
	TcpClient client;
public:
	void SendMassage(string& str);
	void Logic(Windows& window, MyStruct& strct);
};

inline void ClientLogic::SendMassage(string& str)
{
	client.send(str);
}

DWORD WINAPI Getting(LPVOID lp) {
	MyStruct* strct = (struct MyStruct*)lp;
	string response;
	wstring info;

	while (true) {
		response = strct->client.receive();

		if (strstr(response.c_str(), "<JSON>") != NULL &&
			!(strstr(response.c_str(), "404") != NULL)) {
			info = L"Wather: " + strct->GetInfo("main", response) + L"\r\n"
				+ L"Description: " + strct->GetInfo("description", response) + L"\r\n"
				+ L"Temperature: " + strct->GetInfo("temp", response) + L" C" + L"\r\n"
				+ L"Feels like: " + strct->GetInfo("feels_like", response) + L" C" + L"\r\n"
				+ L"Lowest temperature: " + strct->GetInfo("temp_min", response) + L" C" + L"\r\n"
				+ L"Highest temperature: " + strct->GetInfo("temp_max", response) + L" C" + L"\r\n"
				+ L"Pressure: " + strct->GetInfo("pressure", response) + L" hPa" + L"\r\n"
				+ L"Humidity: " + strct->GetInfo("humidity", response) + L" %" + L"\r\n";

			SetDlgItemText(*strct->window->GethDialog(), IDC_WATHER, (LPCWSTR)info.c_str());
		}
		else {
			MessageBox(*strct->window->GethDialog(), L"Town not exist", NULL, MB_OK);
			SetDlgItemText(*strct->window->GethTown(), IDC_WATHER, NULL);
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



