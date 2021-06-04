#pragma once
#include "Header.h"
class WorkWithFile
{
private:
	ofstream in;
	ifstream out;
public:
	string Read(const string& path);
	void Write(const string& path, const string& txt, const bool temp);
};

inline string WorkWithFile::Read(const string& path)
{
	string temp;
	out.open(path, ios::in);

	if (out.is_open()) {
		getline(out, temp);
	}

	out.close();

	return temp;
}

inline void WorkWithFile::Write(const string& path, const string& txt, const bool temp)
{
	if (temp) { in.open(path, ios::app); }
	else { in.open(path, ios::out); }

	if (in.is_open()) {
		in << txt;
	}

	in.close();
}

