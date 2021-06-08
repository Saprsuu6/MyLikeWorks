#pragma once
#include "Header.h"
class Windows
{
private:
	HWND hDialog;
	HWND hTown;
	HWND hSendTown;
	HWND hWather;
	HWND hPictureControl;
public:
	void SetDiscriptors(const HWND& hwnd);
	const HWND* GethDialog() const;
	const HWND* GethTown() const;
	const HWND* GethSendTown() const;
	const HWND* GethWather() const;
	const HWND* GethPictureControl() const;

	void EnableDisableSend() const;
};

inline void Windows::SetDiscriptors(const HWND& hwnd)
{
	hDialog = hwnd;
	hTown = GetDlgItem(hwnd, IDC_TOWN);
	hSendTown = GetDlgItem(hwnd, IDC_SEND_TOWN);
	hWather = GetDlgItem(hwnd, IDC_WATHER);
	hPictureControl = GetDlgItem(hwnd, IDC_PICTURECONTROL);
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

inline const HWND* Windows::GethPictureControl() const
{
	return &hPictureControl;
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