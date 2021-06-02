#include "Header.h"

INT_PTR CALLBACK DialogProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
{
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DialogProc);
}

INT_PTR CALLBACK DialogProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static Windows* window = new Windows();
	static MyStruct* strct = new MyStruct();
	static ClientLogic* client = new ClientLogic();
	static Logic* logic = new Logic();
	string massage;

	switch (uMsg)
	{
	case WM_INITDIALOG:
		strct->window = window;
		window->SetDiscriptors(hwnd);
		client->Logic(*window, *strct);
		window->EnableDisableFindWather(false);
		return TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDC_SEND_TOWN) {
			massage = logic->GetTown(hwnd);
			massage += "<TOWN>";
			client->SendMassage(massage);
			window->EnableDisableFindWather(true);
		}
		else if (LOWORD(wParam) == IDC_FIND_WATHER) {
			massage += "<FIND>";
			client->SendMassage(massage);
			window->EnableDisableFindWather(false);
		}
		return TRUE;

	case WM_CLOSE:
		EndDialog(hwnd, 0);
		return TRUE;
	}

	window->EnableDisableSend();

	return FALSE;
}