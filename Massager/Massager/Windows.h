#pragma once
#include "Header.h"
class Windows
{
private:
	HWND hName;
	HWND hOk;
	HWND hListUsers;
	HWND hMassageField;
	HWND hSend;
	HWND hWrite;
public:
	void SetDiscriptors(const HWND& hwnd);

	const HWND* GethName() const;
	const HWND* GethOk() const;
	const HWND* GethListUsers() const;
	const HWND* GethMassageField() const;
	const HWND* GethSend() const;
	const HWND* GethWrite() const;

	void AddToListBox(string& str);
	void AddToChat(string& str);
};

inline void Windows::AddToListBox(string& str)
{
	wstring temp(str.begin(), str.end());
	SendMessage(hListUsers, LB_ADDSTRING, 0, (LPARAM)temp.c_str());
}

inline void Windows::AddToChat(string& str)
{
	wstring temp(str.begin(), str.end());
	SendMessage(hMassageField, LB_ADDSTRING, 0, (LPARAM)temp.c_str());
}

inline void Windows::SetDiscriptors(const HWND& hwnd)
{
	hName = GetDlgItem(hwnd, IDC_NAME);
	hOk = GetDlgItem(hwnd, IDC_OK);
	hListUsers = GetDlgItem(hwnd, IDC_LIST);
	hMassageField = GetDlgItem(hwnd, IDC_MASSAGE_FIELD);
	hSend = GetDlgItem(hwnd, IDC_SEND);
	hWrite = GetDlgItem(hwnd, IDC_WRITE);
}

inline const HWND* Windows::GethName() const
{
	return &hName;
}

inline const HWND* Windows::GethOk() const
{
	return &hOk;
}

inline const HWND* Windows::GethListUsers() const
{
	return &hListUsers;
}

inline const HWND* Windows::GethMassageField() const
{
	return &hMassageField;
}

inline const HWND* Windows::GethSend() const
{
	return &hSend;
}

inline const HWND* Windows::GethWrite() const
{
	return &hWrite;
}