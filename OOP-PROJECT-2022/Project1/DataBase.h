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
	DataBase(const char* userName = nullptr, const char* password = nullptr, const char* email = nullptr);

	bool isValidName(const char* userName) const;

	friend std::ostream& operator<<(std::ostream& out, const DataBase& rhs);
	friend std::ifstream& operator>>(std::ifstream& in, DataBase& rhs);

	const MyString getUserName() const { return mUserName; }
	const MyString getPassword() const { return mPassword; }
};



#endif


