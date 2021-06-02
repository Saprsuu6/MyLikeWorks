#pragma once
#include "Header.h"
class Path
{
private:
	WCHAR path[MAX_PATH];
public:
	void GetText(const Windows* window);
	const WCHAR* GetPath() const;
};

void Path::GetText(const Windows* window)
{
	GetWindowText(*window->GethEdit(), (LPWSTR)path, MAX_PATH);
}

inline const WCHAR* Path::GetPath() const
{
	return path;
}

