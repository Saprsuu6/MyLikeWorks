#include "Header.h"

INT_PTR CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
{
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_MASSAGER), NULL, DlgProc);
}

INT_PTR CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static Windows* window = new Windows();
	static ClientLogic* clientLogic = new ClientLogic();
	static Logic* logic = new Logic(window, clientLogic);
	static MyStruct* strct = new MyStruct();

	switch (uMsg)
	{
	case WM_INITDIALOG:
		strct->window = window;
		window->SetDiscriptors(hwnd);
		clientLogic->Logic(*window, *strct);
		logic->EnableDisableEditSend(0);
		break;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDC_OK) {
			logic->SendName(hwnd);
			logic->EnableDisableEditSend(1);
			logic->EnableDisableName(hwnd, 0);
		}
		else if (LOWORD(wParam) == IDC_LIST && HIWORD(wParam) == LBN_SELCHANGE) {
			logic->SendIndex();
		}
		else if (LOWORD(wParam) == IDC_SEND) {
			logic->SendMassage(hwnd);
			logic->ClearWrite(hwnd);
		}
		break;

	case WM_CLOSE:
		EndDialog(hwnd, 0);
		return TRUE;
	}

	logic->EnableDisableOK();
	logic->EnableDisableSend();

	return FALSE;
}