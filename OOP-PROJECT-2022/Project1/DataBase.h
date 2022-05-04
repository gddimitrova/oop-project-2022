#ifndef DATABASE_H_INCLUDED
#define DATABASE_H_INCLUDED
#include "MyString.h"

class DataBase
{
private:
	MyString mUserName;
	MyString mPassword;
	MyString mEmail;

public:
	DataBase(const char* userName, const char* password, const char* email);

};



#endif


