#pragma once
#include "Header.h"
class Notice
{
private:
	SYSTEMTIME st;

	wstring _date;
	wstring _notice;

	void SetNotice(const wstring& notice);
public:
	Notice(const wstring& notice);

	void SetTime();
	void SetDate(const wstring& date);
	const wstring* GetDate() const;
	const wstring* GetNotice() const;
};

inline Notice::Notice(const wstring& notice)
{
	GetSystemTime(&st);
	SetNotice(notice);
}

inline void Notice::SetTime()
{
	_date = to_wstring(st.wSecond) + L"." + to_wstring(st.wMinute) + L"." + to_wstring(st.wHour) + L"  "
		+ to_wstring(st.wDay) + L"." + to_wstring(st.wMonth) + L"." + to_wstring(st.wYear);
}

inline void Notice::SetNotice(const wstring& notice)
{
	_notice = notice;
}

inline void Notice::SetDate(const wstring& date)
{
	_date = date;
}

inline const wstring* Notice::GetDate() const
{
	return &_date;
}

inline const wstring* Notice::GetNotice() const
{
	return &_notice;
}
