#include "Header.h"

INT_PTR CALLBACK DialogProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
{
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DialogProc);
}

INT_PTR CALLBACK DialogProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static TcpServer server;
	static Windows* window = new Windows();
	static MyStruct* strct = new MyStruct();
	static ClientLogic* client = new ClientLogic();
	static Logic* logic = new Logic();

	string town;
	string HTTPmassage;
	string answer;

	switch (uMsg)
	{
	case WM_INITDIALOG:
		strct->window = window;
		window->SetDiscriptors(hwnd);
		
		strct->tree.emplace("01d", LoadBitmap(strct->hInstance, MAKEINTRESOURCE(IDB_BITMAP2)));
		strct->tree.emplace("01n", LoadBitmap(strct->hInstance, MAKEINTRESOURCE(IDB_BITMAP3)));
		strct->tree.emplace("02d", LoadBitmap(strct->hInstance, MAKEINTRESOURCE(IDB_BITMAP4)));
		strct->tree.emplace("02n", LoadBitmap(strct->hInstance, MAKEINTRESOURCE(IDB_BITMAP5)));
		strct->tree.emplace("03d", LoadBitmap(strct->hInstance, MAKEINTRESOURCE(IDB_BITMAP6)));
		strct->tree.emplace("03n", LoadBitmap(strct->hInstance, MAKEINTRESOURCE(IDB_BITMAP7)));
		strct->tree.emplace("04d", LoadBitmap(strct->hInstance, MAKEINTRESOURCE(IDB_BITMAP8)));
		strct->tree.emplace("04n", LoadBitmap(strct->hInstance, MAKEINTRESOURCE(IDB_BITMAP9)));
		strct->tree.emplace("09d", LoadBitmap(strct->hInstance, MAKEINTRESOURCE(IDB_BITMAP10)));
		strct->tree.emplace("09n", LoadBitmap(strct->hInstance, MAKEINTRESOURCE(IDB_BITMAP11)));
		strct->tree.emplace("10d", LoadBitmap(strct->hInstance, MAKEINTRESOURCE(IDB_BITMAP12)));
		strct->tree.emplace("10n", LoadBitmap(strct->hInstance, MAKEINTRESOURCE(IDB_BITMAP13)));
		strct->tree.emplace("11d", LoadBitmap(strct->hInstance, MAKEINTRESOURCE(IDB_BITMAP14)));
		strct->tree.emplace("11n", LoadBitmap(strct->hInstance, MAKEINTRESOURCE(IDB_BITMAP15)));
		strct->tree.emplace("13d", LoadBitmap(strct->hInstance, MAKEINTRESOURCE(IDB_BITMAP16)));
		strct->tree.emplace("13n", LoadBitmap(strct->hInstance, MAKEINTRESOURCE(IDB_BITMAP17)));
		strct->tree.emplace("50d", LoadBitmap(strct->hInstance, MAKEINTRESOURCE(IDB_BITMAP18)));
		strct->tree.emplace("50n", LoadBitmap(strct->hInstance, MAKEINTRESOURCE(IDB_BITMAP19)));

		strct->hStaticImage = CreateWindowEx(
			0,
			L"Static",
			L"",
			WS_CHILD | WS_VISIBLE | SS_BITMAP,
			300, 30, 150, 150,
			hwnd,
			0,
			GetModuleHandle(0),
			0);

		server.GetAddresInfo();
		server.ConnectionWithWatherServer();
		return TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDC_SEND_TOWN) {
			town = logic->GetTown(hwnd);
			server.ConnectionWithWatherServer();

			HTTPmassage = server.MakingMassage(town);

			server.FindWather(HTTPmassage);
			answer = server.GetAnswer();

			client->InterpretJson(answer, strct);
		}
		return TRUE;

	case WM_CLOSE:
		EndDialog(hwnd, 0);
		return TRUE;
	}

	window->EnableDisableSend();

	return FALSE;
}