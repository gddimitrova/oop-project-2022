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
	size_t mGrade;
	MyString mComment;
	MyString* mPhotos;
	
	size_t mSize;
	size_t mCapacity;

	void copyFrom(const char** photos, size_t size, size_t capacity);
	void copyFromOther(const PersonalDB& other);
	void free();

public:
	PersonalDB(const char* destination, int day, int month, int year, int dayEnd, int monthEnd, int yearEnd, size_t grade, const char* comment, const char** photos, size_t size);
	PersonalDB(const PersonalDB& other);
	PersonalDB& operator=(const PersonalDB& other);
	~PersonalDB();
};

#endif
