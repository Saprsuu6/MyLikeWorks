#pragma once
#include "Header.h"
class ClientLogic
{
private:
	TcpClient client;
public:
	void SendMassage(string& str);
	void InterpretJson(const string json, MyStruct* strct);
};

inline void ClientLogic::SendMassage(string& str)
{
	client.send(str);
}

inline void ClientLogic::InterpretJson(const string json, MyStruct* strct)
{
	wstring info;

	if (!(strstr(json.c_str(), "404") != NULL)) {
		info = L"Wather: " + strct->GetInfo("main", json) + L"\r\n"
			+ L"Description: " + strct->GetInfo("description", json) + L"\r\n"
			+ L"Temperature: " + strct->GetInfo("temp", json) + L" C" + L"\r\n"
			+ L"Feels like: " + strct->GetInfo("feels_like", json) + L" C" + L"\r\n"
			+ L"Lowest temperature: " + strct->GetInfo("temp_min", json) + L" C" + L"\r\n"
			+ L"Highest temperature: " + strct->GetInfo("temp_max", json) + L" C" + L"\r\n"
			+ L"Pressure: " + strct->GetInfo("pressure", json) + L" hPa" + L"\r\n"
			+ L"Humidity: " + strct->GetInfo("humidity", json) + L" %" + L"\r\n";

		SendMessage(strct->hStaticImage, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)strct->hBitmap);

		SetDlgItemText(*strct->window->GethDialog(), IDC_WATHER, (LPCWSTR)info.c_str());
	}
	else {
		MessageBox(*strct->window->GethDialog(), L"Town not exist", NULL, MB_OK);
		SetDlgItemText(*strct->window->GethTown(), IDC_WATHER, NULL);
	}
}

DWORD WINAPI Getting(LPVOID lp) {
	MyStruct* strct = (struct MyStruct*)lp;
	string response;
	wstring info;

	while (true) {
		response = strct->client.receive();

		
	}

	return 0;
}



