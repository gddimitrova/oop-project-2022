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

void MyString::free()
{
	delete[] mString;
}

MyString::MyString()
{
	mString = new char[DEFAULT_LENGHT];
	mString[0] = '\0';
}

MyString::MyString(const char* newString)
{
	copyDynamic(mString, newString);
}

MyString::MyString(const MyString& other) : MyString(other.mString)
{
}

MyString& MyString::operator=(const MyString& other)
{
	if (this != &other) {
		free();
		copyDynamic(mString, other.mString);
	}
	return *this;
}

MyString::~MyString()
{
	free();
}

std::ostream& operator<<(std::ostream& out, const MyString& rhs)
{
	out << rhs.getString() << std::endl;

	return out;
}
