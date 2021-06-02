#pragma once
class Logic
{
	void PrintError(const HWND& hwnd);
	void AmountProcess(const Windows* window);
	void KillPoroc(const Windows* window, const int index);
	void FillListBox(const Windows* window, const HWND& hwnd);
public:
	void Reset(const Windows* window, const HWND& hwnd);
	void Kill(const Windows* window);
};

inline void Logic::PrintError(const HWND& hwnd)
{
	int errorCode = GetLastError();

	wstring str;
	WCHAR errorMessage[500];
	LPVOID lpBuffer = NULL;

	DWORD res = FormatMessage(
		FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER,
		NULL,
		errorCode,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPWSTR)&lpBuffer,
		0,
		NULL
	);

	str = L"Error";
	str += (wchar_t*)lpBuffer;
	MessageBox(hwnd, str.c_str(), L"Error", MB_OK | MB_ICONWARNING);
}

inline void Logic::AmountProcess(const Windows* window)
{
	wstring str;
	int amount = SendMessage(*window->GethMainList(), LB_GETCOUNT, 0, 0);
	str = L"Amount process: " + to_wstring(amount);
	SetWindowText(*window->GethAmountPr(), str.c_str());
}

inline void Logic::Kill(const Windows* window)
{
	int selCount = SendMessage(*window->GethMainList(), LB_GETSELCOUNT, 0, 0);
	int* selItems = new int[selCount];
	SendMessage(*window->GethMainList(), LB_GETSELITEMS, selCount, LPARAM(selItems));
	
	for (int i = 0; i < selCount; i++) {
		KillPoroc(window, selItems[i]);
	}
}

inline void Logic::Reset(const Windows* window, const HWND& hwnd)
{
	SendMessage(*window->GethMainList(), LB_RESETCONTENT, 0, 0);
	FillListBox(window, hwnd);
}

inline void Logic::KillPoroc(const Windows* window, const int index)
{
	DWORD kill = SendMessage(*window->GethMainList(), LB_GETITEMDATA, index, 0);
	HANDLE processHandle = OpenProcess(PROCESS_ALL_ACCESS, TRUE, kill);
	TerminateProcess(processHandle, 0);
}

inline void Logic::FillListBox(const Windows* window, const HWND& hwnd)
{
	int pos = 0;
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (hSnapshot == NULL) {
		PrintError(hwnd);
	}

	PROCESSENTRY32 processInfo = { sizeof(PROCESSENTRY32) };
	BOOL res = Process32First(hSnapshot, &processInfo);

	if (res == TRUE) {
		do {
			pos = SendMessage(*window->GethMainList(), LB_ADDSTRING, 0, (LPARAM)processInfo.szExeFile);
			SendMessage(*window->GethMainList(), LB_SETITEMDATA, pos, (LPARAM)processInfo.th32ProcessID);
		} 		
		while (Process32Next(hSnapshot, &processInfo)); // получение информации  о сл процессе, записанном в сминок системы
	}

	if (hSnapshot != 0) {
		CloseHandle(hSnapshot);
	}	

	AmountProcess(window);
}