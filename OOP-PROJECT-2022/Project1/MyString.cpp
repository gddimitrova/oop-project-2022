#include "MyString.h"
#include <iostream>

#define DEFAULT_LENGHT 10
#define MAX_LEN 2048

void MyString::copyDynamic(char*& destinaton, const char* source)
{
	if (source) {
		size_t len = strlen(source) + 1;
		destinaton = new char[len];
		strcpy_s(destinaton, len, source);
	}
	else {
		destinaton = nullptr;
	}
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

bool MyString::operator==(const MyString& other) const
{
	return strcmp(mString, other.mString)==0;
}


bool MyString::operator!=(const MyString& other) const 
{
	return !(mString == other.mString);
}

std::ostream& operator<<(std::ostream& out, const MyString& rhs)
{
	out << rhs.getLength() << " " << rhs.getString();

	return out;
}

std::istream& operator>>(std::istream& in, MyString& rhs)
{
	size_t len;
	in >> len;
	in.ignore(); // Тук трябва да игнорираме, защото *
	rhs.mString = new char[len + 1];
	in.get(rhs.mString, len + 1); // * тук четем с get а не със cin, защото може да имаме коментар изречение
								 // и не ползваме getLine, защото се прецаква при случая със снимките

	return in;
}
