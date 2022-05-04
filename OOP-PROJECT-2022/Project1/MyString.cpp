#include "MyString.h"
#include <iostream>

#define DEFAULT_LENGHT 10

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

MyString::MyString(): mLength(DEFAULT_LENGHT) 
{
	mString = new char[mLength + 1];
	mString[0] = '\0';
}

MyString::MyString(const char* newString, size_t newLen)
{
	copyFrom(newString, newLen);
}

MyString::MyString(const MyString& other): MyString(other.mString, other.mLength)
{
}

MyString& MyString::operator=(const MyString& other)
{
	if (this != &other) {
		free();
		copyFrom(other.mString, other.mLength);
	}
	return *this;
}

MyString::~MyString()
{
	free();
}
