#include "Header.h"

INT_PTR CALLBACK DialogProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
{
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DialogProc);
}

INT_PTR CALLBACK DialogProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static Facade* facade = new Facade();
	facade->EnableDisableButton();

	switch (uMsg)
	{
	case WM_INITDIALOG:
		facade->SetDescriptors(hwnd);
		EnableWindow(*facade->GetWindowsDescriptors()->GethAdd(), FALSE);
		EnableWindow(*facade->GetWindowsDescriptors()->GethClear(), FALSE);
		EnableWindow(*facade->GetWindowsDescriptors()->GethDelete(), FALSE);
		EnableWindow(*facade->GetWindowsDescriptors()->GethChange(), FALSE);
		if (facade->FileExists("Noties\\*.dll")) {
			facade->ReadNoties();
		}
		break;

	case WM_COMMAND:
		facade->SetLogic(hwnd, uMsg, wParam, lParam);
		break;

	case WM_CLOSE:
		facade->SaveNoties();
		EndDialog(hwnd, 0);
		return TRUE;
	}

	return FALSE;
}