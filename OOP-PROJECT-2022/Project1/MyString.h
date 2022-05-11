#ifndef MYSTRING_H_INCLUDED
#define MYSTRING_H_INCLUDED
#include <cstring>
#include <fstream>

class MyString
{
private:
	char* mString;
	
	void copyDynamic(char*& destinaton, const char* source);
	void free();
public:
	MyString();
	MyString(const char* newString);
	MyString(const MyString& other);
	MyString& operator=(const MyString& other);
	~MyString();

	size_t getLength() const { return strlen(mString); }
	const char* getString() const { return mString; }

	friend std::ostream& operator<<(std::ostream& out, const MyString& rhs);
	friend std::istream& operator>>(std::istream& in, MyString& rhs);

	bool operator==(const MyString& other) const;
	bool operator!=(const MyString& other) const;

};

#endif 



