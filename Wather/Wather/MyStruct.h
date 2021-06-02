#pragma once
#include "Header.h"
struct MyStruct
{
	TcpClient client;
	Windows* window = nullptr;

	wstring GetInfo(const string& key_word, const string& json) {
		size_t size_key_word = key_word.length() + 2;
		size_t size_json = json.length();
		size_t index = json.find(key_word);
		wstring temp;

		for (size_t i = index + size_key_word; i < size_json; i++) {
			if ((json[i] >= 'A' && json[i] <= 'Z') || (json[i] >= 'a' && json[i] <= 'z')
				|| (json[i] >= '0' && json[i] <= '9') || json[i] == '.' || json[i] == ' ') {
				temp += json[i];
			}
			else if (json[i] == '}' || json[i] == ',' || (json[i] == '"' && (json[i - 1] >= 'a' && json[i - 1] <= 'z'))) {
				break;
			}
		}

		return temp;
	}
};

