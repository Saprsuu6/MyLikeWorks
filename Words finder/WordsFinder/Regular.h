#pragma once
#include "Header.h"
class Regular
{
public:
	void Cheking(string& text, MyStruct& strct);
};

inline void Regular::Cheking(string& text, MyStruct& strct)
{
	string origWord;
	string temp;
	size_t position = 0;
	size_t size = 0;
	size_t amount = strct.notAcceptWords.size();

	for (size_t i = 0; i < amount; i++) {
		sregex_iterator beg{ strct.text.cbegin(), strct.text.cend(), strct.notAcceptWords[i] };
		sregex_iterator end{};

		for (sregex_iterator i = beg; i != end; i++) {
			position = i->position();
			size = i->length() + position;

			for (size_t j = position; j < size; j++) {
				origWord.push_back(text[j]);

				if (text[j] != '-' && text[j] != '+' && text[j] != '(' && text[j] != ')'
					&& text[j] != '*' && text[j] != '@') {

					text[j] = '*';
				}
				temp += text[j];
			}

			strct.allWords.push_back(origWord);
			strct.words.push_back(temp);
			temp.clear();
		}
	}
}





