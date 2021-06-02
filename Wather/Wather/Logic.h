#pragma once
#include "Header.h"
class Logic
{
public:
	string GetTown(const HWND& hwnd);
};

string Logic::GetTown(const HWND& hwnd)
{
	WCHAR hMainList[MAX_PATH];
	GetDlgItemText(hwnd, IDC_TOWN, hMainList, MAX_PATH);
	wstring temp(hMainList);
	string town(temp.begin(), temp.end());

	return town;
}
