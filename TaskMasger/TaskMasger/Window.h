#pragma once
#include "Header.h"
class Windows
{
private:
	HWND hRestet;
	HWND hKillProcess;
	HWND hMainList;
	HWND hEdit;
	HWND hCreateProcess;
	HWND hAmountPr;
public:
	void SetDiscriptors(const HWND& hwnd);
	const HWND* GethRestet() const;
	const HWND* GethKillProcess() const;
	const HWND* GethMainList() const;
	const HWND* GethEdit() const;
	const HWND* GethCreateProcess() const;
	const HWND* GethAmountPr() const;

	void EnableDisableButton();
};

inline void Windows::SetDiscriptors(const HWND& hwnd)
{
	hRestet = GetDlgItem(hwnd, IDC_RESET);
	hKillProcess = GetDlgItem(hwnd, IDC_KILLPR);
	hMainList = GetDlgItem(hwnd, IDC_MAIN_LIST);
	hEdit = GetDlgItem(hwnd, IDC_EDIT);
	hCreateProcess = GetDlgItem(hwnd, IDC_CREATEPR);
	hAmountPr = GetDlgItem(hwnd, IDC_AMOUNTPR);
}

inline const HWND* Windows::GethRestet() const
{
	return &hRestet;
}

inline const HWND* Windows::GethKillProcess() const
{
	return &hKillProcess;
}

inline const HWND* Windows::GethMainList() const
{
	return &hMainList;
}

inline const HWND* Windows::GethEdit() const
{
	return &hEdit;
}

inline const HWND* Windows::GethCreateProcess() const
{
	return &hCreateProcess;
}

inline const HWND* Windows::GethAmountPr() const
{
	return &hAmountPr;
}

inline void Windows::EnableDisableButton()
{
	int length = SendMessage(*GethEdit(), WM_GETTEXTLENGTH, 0, 0);
	if (length > 0) {
		EnableWindow(*GethCreateProcess(), TRUE);
	}
	else {
		EnableWindow(*GethCreateProcess(), FALSE);
	}

	if (SendMessage(*GethMainList(), LB_GETCURSEL, 0, 0) < 0) {
		EnableWindow(*GethKillProcess(), FALSE);
	}
	else {
		EnableWindow(*GethKillProcess(), TRUE);
	}
}

