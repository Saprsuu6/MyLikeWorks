#pragma once
#include "Header.h"
struct MyStruct {
	bool exitTemp = false;
	int counter = 0;
	int counterResult = 0;
	_fsize_t size = 0;
	string path;
	string temp_path;
	string text;
	string atribute;
	string fileName;
	string repFileName;
	vector<string> notAcceptWords;
	vector<string> words;
	WorkWithFile* file = nullptr;
	Windows* window = nullptr;

	HANDLE searching;
	HANDLE changing;

	HANDLE mutexWriter, mutexReader;
	HANDLE hEvent;

	void SetAtribute(const _finddata_t fileinfo) {
		if (fileinfo.attrib & _A_NORMAL) {
			atribute = "normal";
		}
		else if (fileinfo.attrib & _A_ARCH) {
			atribute = "Arichive";
		}
		else if (fileinfo.attrib & _A_HIDDEN) {
			atribute = "Hidden";
		}
		else if (fileinfo.attrib & _A_RDONLY) {
			atribute = "Read only";
		}
		else if (fileinfo.attrib & _A_SUBDIR) {
			atribute = "Direcoties";
		}
		else if (fileinfo.attrib & _A_SYSTEM) {
			atribute = "System file";
		}
	}
};