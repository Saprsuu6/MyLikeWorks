#pragma once
#include "Header.h"
class Regular
{
private:
	regex* rex = nullptr;
	size_t amount = 0;
public:
	Regular(const size_t amount);
	void Fill(const MyStruct& strct);
	void Cheking(string& text, MyStruct& strct);
};

Regular::Regular(const size_t amount)
{
	rex = new regex[amount];
	this->amount = amount;
}

inline void Regular::Fill(const MyStruct& strct)
{
	for (int i = 0; i < amount; i++) {
		rex[i] = strct.notAcceptWords[i];
	}
}

inline void Regular::Cheking(string& text, MyStruct& strct)
{
	string temp;

	for (int i = 0; i < amount; i++) {
		sregex_iterator beg{ strct.text.cbegin(), strct.text.cend(), rex[i] };
		sregex_iterator end{};

		for (sregex_iterator i = beg; i != end; i++) {
			size_t size = i->length();

			for (size_t j = 0; j < size; j++) {
				if (text[j] != '-' && text[j] != '+' && text[j] != '(' && text[j] != ')') {
					text[j] = '*';
				}
				temp = text[j];
			}

			strct.words.push_back(temp);
		}
	}
}





