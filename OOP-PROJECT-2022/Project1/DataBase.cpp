#include "DataBase.h"
#include <cctype>

DataBase::DataBase(const char* userName, const char* password, const char* email):mPassword(password), mEmail(email)
{
    if (!isValidName(userName))
        throw std::exception("Invalid name!");
    mUserName = userName;
}

bool DataBase::isValidName(const char* userName) const
{
    int i = 0;
    while (userName[i] != '\0') {
        if (isdigit(userName[i]) && isalpha(userName[i]))
            return false;
        i++;
    }

    return true;
}

std::ostream& operator<<(std::ostream& out, const DataBase& rhs)
{
    out << rhs.mUserName.getLength() << " " << rhs.mUserName << " "
        << rhs.mPassword.getLength() << " " << rhs.mPassword << " "
        << rhs.mEmail.getLength() << " " << rhs.mEmail << std::endl;

    return out;
}
