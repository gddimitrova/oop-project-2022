#ifndef MYSTRING_H_INCLUDED
#define MYSTRING_H_INCLUDED


class MyString
{
private:
	char* mString;
	size_t mLength;
	
	void copyDynamic(char*& destinaton, const char* source);
	void copyFrom(const char* otherString, size_t otherLen);
	void free();
public:
	MyString();
	MyString(const char* newString, size_t newLen);
	MyString(const MyString& other);
	MyString operator=(const MyString& other);
	~MyString();

};

#endif 



