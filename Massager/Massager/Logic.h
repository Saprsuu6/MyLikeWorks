#pragma once
#include "Header.h"
class Logic
{
private:
	Windows* window = nullptr;
	ClientLogic* clientLogic = nullptr;
public:
	Logic(Windows* window, ClientLogic* clientLogic);

	void EnableDisableName(const HWND& hwnd, const int temp) const;
	void EnableDisableOK() const;
	void EnableDisableEditSend(const int temp) const;
	void EnableDisableSend() const;
	void SendName(const HWND& hwnd) const;
	void SendMassage(const HWND& hwnd) const;
	void SendIndex() const;
	void ClearWrite(const HWND& hwnd) const;
};

inline void Logic::EnableDisableName(const HWND& hwnd, const int temp) const
{
	EnableWindow(*window->GethName(), temp);
}

inline void Logic::ClearWrite(const HWND& hwnd) const
{
	SetDlgItemText(hwnd, IDC_WRITE, 0);
}

Logic::Logic(Windows* window, ClientLogic* clientLogic)
{
	if (window != nullptr && clientLogic != nullptr) {
		this->window = window;
		this->clientLogic = clientLogic;
	}
}

inline void Logic::EnableDisableOK() const
{
	int length = SendMessage(*window->GethName(), WM_GETTEXTLENGTH, 0, 0);
	if (length > 0) {
		EnableWindow(*window->GethOk(), TRUE);
	}
	else {
		EnableWindow(*window->GethOk(), FALSE);
	}
}

inline void Logic::EnableDisableSend() const
{
	int length = SendMessage(*window->GethWrite(), WM_GETTEXTLENGTH, 0, 0);
	if (length > 0) {
		EnableWindow(*window->GethSend(), TRUE);
	}
	else {
		EnableWindow(*window->GethSend(), FALSE);
	}
}

inline void Logic::SendName(const HWND& hwnd) const
{
	WCHAR name[MAX_PATH];
	GetDlgItemText(hwnd, IDC_NAME, name, MAX_PATH);

	wstring temp(name);
	string temp2(temp.begin(), temp.end());
	temp2 += "<CHNG>";
	
	clientLogic->SendMassage(temp2);
}

inline void Logic::SendIndex() const
{
	int index = SendMessage(*window->GethListUsers(), LB_GETCURSEL, 0, 0);
	string temp = to_string(index) + "<LIST>";

	clientLogic->SendMassage(temp);
}

inline void Logic::SendMassage(const HWND& hwnd) const
{
	int length = SendMessage(*window->GethWrite(), WM_GETTEXTLENGTH, 0, 0);

	WCHAR* text = new WCHAR[length];
	GetDlgItemText(hwnd, IDC_WRITE, (LPWSTR)text, MAX_PATH);

	wstring wstr(text);
	string str(wstr.begin(), wstr.end());
	str += "<TEXT>";

	clientLogic->SendMassage(str);
}

inline void Logic::EnableDisableEditSend(const int temp) const
{
	EnableWindow(*window->GethSend(), temp);
	EnableWindow(*window->GethWrite(), temp);
}


