#pragma once
#include "Header.h"
class NotAllowFile : public exception
{
public:
	NotAllowFile(const string& error) : exception(error.c_str()) {};
};

