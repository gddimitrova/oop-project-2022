#include "MyString.h"
#include <iostream>

void MyString::copyDynamic(char*& destinaton, const char* source)
{
	if (source) {
		int len = strlen(source) + 1;
		destinaton = new char[len];
		strcpy_s(destinaton, len, source);
	}
	else
		destinaton = nullptr;
}

void MyString::copyFrom(const char* otherString, size_t otherLen)
{
	mLength = otherLen;
	copyDynamic(mString, otherString);
}

void MyString::free()
{
	delete[] mString;
}
