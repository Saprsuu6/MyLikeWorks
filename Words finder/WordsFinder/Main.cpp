#include "Header.h"

INT_PTR CALLBACK DialogProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
{
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DialogProc);
}

void ReadNotAllowWords(MyStruct* strct)
{
	string word;
	ifstream out;

	out.open("Words.txt", ios::in);

	if (out.is_open()) {
		while (!out.eof()) {
			getline(out, word);

			strct->notAcceptWords.push_back(word);
		}
	}

	out.close();
}

INT_PTR CALLBACK DialogProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static bool stopBool = false;
	static Windows* window = new Windows();
	static WorkWithFile* file = new WorkWithFile();
	static MyStruct* strct = new MyStruct();

	static string words;
	static wstring temp;
	
	static size_t size = 0;

	switch (uMsg) {
	case WM_INITDIALOG:

		strct->mutexReader = CreateMutex(NULL, FALSE, TEXT("{837F896A-FAF8-46A9-ABF4-25AECAF2961D}"));
		strct->mutexWriter = CreateMutex(NULL, FALSE, TEXT("{5A8353FC-EA39-4686-90AD-045681D2A5BB}"));
		strct->hEvent = CreateEvent(NULL, TRUE, FALSE, TEXT("{9703B13C-278D-4E1F-AAAD-DF2BEC8B4282}"));

		window->SetDiscriptors(hwnd);
		window->DisAnStop(0);
		strct->window = window;
		strct->file = file;
		ReadNotAllowWords(strct);
		break;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDC_START) {
			strct->path = window->GetPath(hwnd);
			window->DisAnStop(1);
			window->DisAnPath(0);
			strct->searching = CreateThread(0, 0, LPTHREAD_START_ROUTINE(Searching), strct, 0, 0);
			strct->changing = CreateThread(0, 0, LPTHREAD_START_ROUTINE(Changing), strct, 0, 0);
		}
		else if (LOWORD(wParam) == IDC_STOP && !stopBool) {
			SuspendThread(strct->searching);
			SuspendThread(strct->changing);
			temp = L"Resume";
			window->ChangeButtonText(temp);
			stopBool = true;
		}
		else if (LOWORD(wParam) == IDC_STOP && stopBool) {
			ResumeThread(strct->searching);
			ResumeThread(strct->changing);
			temp = L"Stop";
			window->ChangeButtonText(temp);
			stopBool = false;
		}
		break;

	case WM_CLOSE:
		EndDialog(hwnd, 0);
		return TRUE;
	}

	window->DisAnStart();

	return FALSE;
}