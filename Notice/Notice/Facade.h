#pragma once
#include "Header.h"
class Facade
{
private:
	Windows* _window = nullptr;
	Notices* _notices = nullptr;

	wifstream fin;
	wofstream fout;

	void DeleteItem(int& itemIndex, int& indexMass);
	void Vrite(const wstring& text, const wstring& path, wofstream& fout);
	void Read(wstring& text, wstring& path, wifstream& fin);
public:
	Facade();

	void EnableDisableButton();
	void SetDescriptors(const HWND& hwnd);
	const Windows* GetWindowsDescriptors() const;

	void SetLogic(const HWND& hwnd, const UINT& uMsg,
		const WPARAM& wParam, const LPARAM& lParam);

	void SaveNoties();
	void ReadNoties();
	bool FileExists(const char* fname);
};

inline bool Facade::FileExists(const char* fname)
{
	_finddata_t data;
	int nFind = _findfirst(fname, &data);
	if (nFind == -1) {
		return false;
	}

	return true;
}

Facade::Facade()
{
	_window = new Windows();
	_notices = new Notices();
}

void Facade::EnableDisableButton()
{
	int length = SendMessage(*_window->GethEditor(), WM_GETTEXTLENGTH, 0, 0); 
	if (length > 0) {
		EnableWindow(*_window->GethAdd(), TRUE);
		EnableWindow(*_window->GethClear(), TRUE);
	}
	else {
		EnableWindow(*_window->GethAdd(), FALSE);
		EnableWindow(*_window->GethClear(), FALSE);
	}
}

inline void Facade::SetDescriptors(const HWND& hwnd)
{
	_window->SetDiscriptors(hwnd);
}

inline const Windows* Facade::GetWindowsDescriptors() const
{
	return _window;
}

inline void Facade::DeleteItem(int& itemIndex, int& indexMass)
{
	itemIndex = SendMessage(*_window->GethMainList(), LB_GETCURSEL, 0, 0);

	if (itemIndex != LB_ERR) {
		indexMass = SendMessage(*_window->GethMainList(), LB_GETITEMDATA, itemIndex, 0);
		SendMessage(*_window->GethMainList(), LB_DELETESTRING, itemIndex, 0);

		_notices->DeleteNotice(indexMass - 1);
	}

	SetWindowText(*_window->GethForRead(), NULL);
}

inline void Facade::Vrite(const wstring& text, const wstring& path, wofstream& fout)
{
	fout.open(path, ios::out);

	if (!fout.is_open()) {
		MessageBox(NULL, L"File is not opened", L"Error", MB_OK);
		return;
	}

	fout << text;
	fout.close();
}

inline void Facade::SaveNoties()
{
	wstring text = L"";
	wstring path = L"";
	const Notice* notice = nullptr;
	int size = SendMessage(*_window->GethMainList(), LB_GETCOUNT, 0, 0);

	fout.open(L"Noties\\Size.dll", ios::binary | ios::out);

	if (!fout.is_open()) {
		MessageBox(NULL, L"File is not opened", L"Error", MB_OK);
		return;
	}

	fout.write((wchar_t*)&size, sizeof size);
	fout.close();

	for (int i = 0; i < size; i++) {
		notice = _notices->GetNotice(i);

		text = *notice->GetNotice();
		path = L"Noties\\" + to_wstring(i) + L".dll";
		Vrite(text, path, fout);

		text = *notice->GetDate();
		path = L"Noties\\Date" + to_wstring(i) + L".dll";
		Vrite(text, path, fout);
	}
}

inline void Facade::Read(wstring& text, wstring& path, wifstream& fin)
{
	fin.open(path, ios::in);

	if (!fin.is_open()) {
		MessageBox(NULL, L"File is not opened", L"Error", MB_OK);
		return;
	}

	getline(fin, text);
	fin.close();
}

inline void Facade::ReadNoties()
{
	wstring date = L"";
	wstring text = L"";
	wstring path = L"";
	Notice* notice = nullptr;
	int size = 0;
	int pos = 0;
	
	fin.open(L"Noties\\Size.dll", ios::binary | ios::out);

	if (!fin.is_open()) {
		MessageBox(NULL, L"File is not opened", L"Error", MB_OK);
		return;
	}

	fin.read((wchar_t*)&size, sizeof size);
	fin.close();
	
	for (int i = 0; i < size; i++) {
		path = L"Noties\\" + to_wstring(i) + L".dll";
		Read(text, path, fin);

		path = L"Noties\\Date" + to_wstring(i) + L".dll";
		Read(date, path, fin);

		notice = new Notice(text);
		notice->SetDate(date);
		_notices->AddNotice(notice);

		pos = SendMessage(*_window->GethMainList(), LB_ADDSTRING, 0, (LPARAM)text.c_str());
		SendMessage(*_window->GethMainList(), LB_SETITEMDATA, pos, _notices->GetSize());
	}
}

inline void Facade::SetLogic(const HWND& hwnd, const UINT& uMsg,
	const WPARAM& wParam, const LPARAM& lParam)
{
	int indexMass = 0;
	int itemIndex = 0;
	int isDelete = 0;
	int pos = 0;
	int iIndex = 0;
	const Notice* notice = nullptr;
	wstring text = L"";;
	WCHAR str[MAX_PATH];

	if (LOWORD(wParam) == IDC_MAIN_LIST && HIWORD(wParam) == LBN_SELCHANGE) {
		text = L"";

		iIndex = SendMessage(*_window->GethMainList(), LB_GETCURSEL, 0, 0);
		notice = _notices->GetNotice(iIndex);

		text = *notice->GetNotice() + L"\r\n\r\n" + L"Date added:\r\n" + *notice->GetDate();
		SetWindowText(*_window->GethForRead(), text.c_str());

		EnableWindow(*_window->GethDelete(), TRUE);
		EnableWindow(*_window->GethChange(), TRUE);
	}
	else if (LOWORD(wParam) == IDC_ADD && HIWORD(wParam) == BN_CLICKED) {
		WCHAR hMainList[MAX_PATH];
		GetDlgItemText(hwnd, IDC_EDITOR, hMainList, MAX_PATH);
		
		Notice* notice = new Notice(hMainList);
		notice->SetTime();

		_notices->AddNotice(notice);

		pos = SendMessage(*_window->GethMainList(), LB_ADDSTRING, 0, LPARAM(hMainList));
		SendMessage(*_window->GethMainList(), LB_SETITEMDATA, pos, _notices->GetSize());
		SetDlgItemText(hwnd, IDC_EDITOR, 0);
	}
	else if (LOWORD(wParam) == IDC_CLEAR && HIWORD(wParam) == BN_CLICKED) {
		SetDlgItemText(hwnd, IDC_EDITOR, 0);
	}
	else if (LOWORD(wParam) == IDC_DELETE && HIWORD(wParam) == BN_CLICKED) {
		isDelete = MessageBox(hwnd, L"Delete?", L"", MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2);

		if (isDelete == IDYES) {
			DeleteItem(itemIndex, indexMass);
		}
	}
	else if (LOWORD(wParam) == IDC_CHANGE && HIWORD(wParam) == BN_CLICKED) {
		iIndex = SendMessage(*_window->GethMainList(), LB_GETCURSEL, 0, 0);
		notice = _notices->GetNotice(iIndex);

		text = *notice->GetNotice();
		SetWindowText(*_window->GethEditor(), text.c_str());

		DeleteItem(itemIndex, indexMass);
	}

	if (SendMessage(*_window->GethMainList(), LB_GETCURSEL, 0, 0) < 0) {
		EnableWindow(*_window->GethDelete(), FALSE);
		EnableWindow(*_window->GethChange(), FALSE);
	}
}

