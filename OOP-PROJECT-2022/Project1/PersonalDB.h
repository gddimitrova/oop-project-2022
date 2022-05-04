#ifndef PERSONALDB_H_INCLUDED
#define PERSONALDB_H_INCLUDED
#include "MyString.h"
#include "Date.h"
class PersonalDB
{
private:
	MyString mDestination;
	Date mStart;
	Date mEnd;
	int grade;
	MyString mComment;
	MyString* mPhotos;
	
	size_t mSize;
	size_t mCapacity;

public:
	PersonalDB(const char* destination, int day, int month, int year, int grade, const char* comment, const char** photos, size_t size);
	PersonalDB(const PersonalDB& other);
	PersonalDB& operator=(const PersonalDB& other);
	~PersonalDB();
};

#endif
