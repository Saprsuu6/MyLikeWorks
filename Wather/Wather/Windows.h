#pragma once
#include "Header.h"
class Windows
{
private:
	HWND hDialog;
	HWND hTown;
	HWND hSendTown;
	HWND hWather;
	HWND hFindWather;
public:
	void SetDiscriptors(const HWND& hwnd);
	const HWND* GethDialog() const;
	const HWND* GethTown() const;
	const HWND* GethSendTown() const;
	const HWND* GethWather() const;
	const HWND* GethFindWather() const;

	void EnableDisableSend() const;
	void EnableDisableFindWather(const bool temp) const;
};

inline void Windows::SetDiscriptors(const HWND& hwnd)
{
	hDialog = hwnd;
	hTown = GetDlgItem(hwnd, IDC_TOWN);
	hSendTown = GetDlgItem(hwnd, IDC_SEND_TOWN);
	hWather = GetDlgItem(hwnd, IDC_WATHER);
	hFindWather = GetDlgItem(hwnd, IDC_FIND_WATHER);
}

inline const HWND* Windows::GethDialog() const
{
	return &hDialog;
}

inline const HWND* Windows::GethTown() const
{
	return &hTown;
}

inline const HWND* Windows::GethSendTown() const
{
	return &hSendTown;
}

inline const HWND* Windows::GethWather() const
{
	return &hWather;
}

inline const HWND* Windows::GethFindWather() const
{
	return &hFindWather;
}

inline void Windows::EnableDisableSend() const
{
	int length = SendMessage(hTown, WM_GETTEXTLENGTH, 0, 0);

	if (length > 0) {
		EnableWindow(hSendTown, TRUE);
	}
	else {
		EnableWindow(hSendTown, FALSE);
	}
}

inline void Windows::EnableDisableFindWather(const bool temp) const
{
	EnableWindow(hFindWather, temp);
}