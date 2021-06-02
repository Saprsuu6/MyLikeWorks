#pragma once
#include "Header.h"
class Windows
{
private:
	HWND _main_list;
	HWND _for_read;
	HWND _editor;
	HWND _add;
	HWND _clear;
	HWND _delete;
	HWND _change;
public:
	void SetDiscriptors(const HWND& hwnd);
	const HWND* GethMainList() const;
	const HWND* GethForRead() const;
	const HWND* GethEditor() const;
	const HWND* GethAdd() const;
	const HWND* GethClear() const;
	const HWND* GethDelete() const;
	const HWND* GethChange() const;
};

inline void Windows::SetDiscriptors(const HWND& hwnd)
{
	_main_list = GetDlgItem(hwnd, IDC_MAIN_LIST);
	_for_read = GetDlgItem(hwnd, IDC_FOR_READ);
	_editor = GetDlgItem(hwnd, IDC_EDITOR);
	_add = GetDlgItem(hwnd, IDC_ADD);
	_clear = GetDlgItem(hwnd, IDC_CLEAR);
	_delete = GetDlgItem(hwnd, IDC_DELETE);
	_change = GetDlgItem(hwnd, IDC_CHANGE);
}

inline const HWND* Windows::GethMainList() const
{
	return &_main_list;
}

inline const HWND* Windows::GethForRead() const
{
	return &_for_read;
}

inline const HWND* Windows::GethEditor() const
{
	return &_editor;
}

inline const HWND* Windows::GethAdd() const
{
	return &_add;
}

inline const HWND* Windows::GethClear() const
{
	return &_clear;
}

inline const HWND* Windows::GethDelete() const
{
	return &_delete;
}

inline const HWND* Windows::GethChange() const
{
	return &_change;
}

