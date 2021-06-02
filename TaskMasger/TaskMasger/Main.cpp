#include "Header.h"

INT_PTR CALLBACK DialogProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
{
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DialogProc);
}

INT_PTR CALLBACK DialogProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static Logic* logic = new Logic();
	static Windows* window = new Windows();
	static Path* path = new Path();
	static Process* process = new Process();
	window->EnableDisableButton();

	switch (uMsg)
	{
	case WM_INITDIALOG:
		window->SetDiscriptors(hwnd);
		EnableWindow(*window->GethKillProcess(), FALSE);
		logic->Reset(window, hwnd);
		break;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDC_RESET) {
			logic->Reset(window, hwnd);
		}
		else if (LOWORD(wParam) == IDC_KILLPR) {
			logic->Kill(window);
			logic->Reset(window, hwnd);
		}
		else if (LOWORD(wParam) == IDC_CREATEPR) {
			path->GetText(window);
			process->OpenProcess(hwnd, path, window);
			logic->Reset(window, hwnd);
		}
		break;

	case WM_CLOSE:
		EndDialog(hwnd, 0);
		return TRUE;
	}

	return FALSE;
}