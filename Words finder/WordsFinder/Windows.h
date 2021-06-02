#pragma once
#include "Header.h"
class Windows
{
private:
	HWND hList;
	HWND hStart;
	HWND hStop;
	HWND hProgress;
	HWND hPath;
public:
	void SetDiscriptors(const HWND& hwnd);
	const HWND* GethList() const;
	const HWND* GethStart() const;
	const HWND* GethStop() const;
	const HWND* GethProgress() const;
	const HWND* GethPath() const;

	void DisAnStart() const;
	void DisAnPath(const int temp) const;
	void DisAnStop(const int temp) const;
	string GetPath(const HWND& hwnd);
	void ChangeButtonText(wstring& txt) const;
	void SetProgress(wstring& txt) const;
	void FinishWork() const;
};

inline void Windows::FinishWork() const
{
	SetWindowText(hProgress, NULL);
	DisAnPath(1);
	EnableWindow(hStop, FALSE);
}

inline void Windows::SetProgress(wstring& txt) const
{
	SetWindowText(hProgress, txt.c_str());
}

inline void Windows::ChangeButtonText(wstring& txt) const
{
	SetWindowText(hStop, txt.c_str());
}

inline void Windows::DisAnStart() const
{
	LRESULT length = SendMessage(hPath, WM_GETTEXTLENGTH, 0, 0);
	if (length > 0) {
		EnableWindow(hStart, TRUE);
	}
	else {
		EnableWindow(hStart, FALSE);
	}
}

inline void Windows::DisAnPath(const int temp) const
{
	SetWindowText(hPath, NULL);
	EnableWindow(hPath, temp);
}

inline void Windows::DisAnStop(const int temp) const
{
	EnableWindow(hStop, temp);
}

inline string Windows::GetPath(const HWND& hwnd)
{
	WCHAR hMainList[MAX_PATH];
	GetDlgItemText(hwnd, IDC_PATH, hMainList, MAX_PATH);
	wstring temp1(hMainList);
	string temp2(temp1.begin(), temp1.end());

	return temp2;
}

inline void Windows::SetDiscriptors(const HWND& hwnd)
{
	hList = GetDlgItem(hwnd, IDC_LIST);
	hStart = GetDlgItem(hwnd, IDC_START);
	hStop = GetDlgItem(hwnd, IDC_STOP);
	hProgress = GetDlgItem(hwnd, IDC_PROGRESS);
	hPath = GetDlgItem(hwnd, IDC_PATH);
}

inline const HWND* Windows::GethList() const
{
	return &hList;
}

inline const HWND* Windows::GethStart() const
{
	return &hStart;
}

inline const HWND* Windows::GethStop() const
{
	return &hStop;
}

inline const HWND* Windows::GethProgress() const
{
	return &hProgress;
}

inline const HWND* Windows::GethPath() const
{
	return &hPath;
}