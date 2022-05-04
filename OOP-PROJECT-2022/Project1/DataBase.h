#ifndef DATABASE_H_INCLUDED
#define DATABASE_H_INCLUDED
#include "MyString.h"
#include <fstream>

class DataBase
{
private:
	MyString mUserName;
	MyString mPassword;
	MyString mEmail;


public:
	DataBase(const char* userName, const char* password, const char* email);

	bool isValidName(const char* userName) const;

	friend std::ostream& operator<<(std::ostream& out, const DataBase& rhs);
};



#endif


