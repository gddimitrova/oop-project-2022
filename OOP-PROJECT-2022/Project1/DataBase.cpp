#include "DataBase.h"
#include <cctype>

DataBase::DataBase(const char* userName, const char* password, const char* email):mPassword(password), mEmail(email)
{
    if (userName != nullptr && !isValidName(userName))
        throw std::exception("Invalid username! Please use only digits and latin letters!");
    mUserName = userName;
}

bool DataBase::isValidName(const char* userName) const
{
    int i = 0;
    while (userName[i] != '\0') {
        if (!isdigit(userName[i]) && !isalpha(userName[i]))
            return false;
        i++;
    }

    return true;
}

std::ostream& operator<<(std::ostream& out, const DataBase& rhs)
{
    out << rhs.mUserName << " "
        << rhs.mPassword << " "
        << rhs.mEmail << std::endl;

    return out;
}

std::ifstream& operator>>(std::ifstream& in, DataBase& rhs)
{
    in >> rhs.mUserName;
    in >> rhs.mPassword;
    in >> rhs.mEmail;

    return in;
}
