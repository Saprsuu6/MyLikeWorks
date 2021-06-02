#pragma once
#include "Header.h"
class Notices
{
private:
	vector<Notice*> _vNotice;
public:
	void AddNotice(Notice* notice);
	void DeleteNotice(const int index);
	void Sort();
	size_t GetSize() const;
	const Notice* GetNotice(const int index);
};

inline void Notices::AddNotice(Notice* notice)
{
	_vNotice.push_back(notice);
}

inline void Notices::DeleteNotice(const int index)
{
	_vNotice.erase(_vNotice.begin() + index);
}

inline void Notices::Sort()
{
	sort(_vNotice.begin(), _vNotice.end());
}

inline size_t Notices::GetSize() const
{
	return _vNotice.size();
}

inline const Notice* Notices::GetNotice(const int index)
{
	return _vNotice[index];
}

