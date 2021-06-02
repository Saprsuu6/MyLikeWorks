#pragma once
#include "Header.h"
class Process
{
private:
	HANDLE hProcess = NULL;
public:
	void OpenProcess(const HWND& hwnd, const Path* path, const Windows* window);
};

inline void Process::OpenProcess(const HWND& hwnd, const Path* path, const Windows* window)
{
	STARTUPINFO startupInfo = { sizeof(STARTUPINFO) };
	PROCESS_INFORMATION processInfo;

	BOOL res = CreateProcess(path->GetPath(), NULL, NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &startupInfo, &processInfo);

	if (res == FALSE) {
		MessageBox(hwnd, L"Error", L"", MB_OK);
		SetWindowText(*window->GethEdit(), NULL);
	}
}


