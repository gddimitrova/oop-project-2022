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
        if (!isdigit(userName[i]) || !isalpha(userName[i]))
            return false;
        i++;
    }

    return true;
}
