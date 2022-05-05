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

	void copyFrom(const char** photos, size_t size);
	void copyFromOther(const PersonalDB& other);
	void free();
	void resize(size_t newSize);

public:
	PersonalDB(size_t capacity);
	PersonalDB(const char* destination, int day, int month, int year, int dayEnd, int monthEnd, int yearEnd, size_t grade, const char* comment, const char** photos, size_t size);
	PersonalDB(const PersonalDB& other);
	PersonalDB& operator=(const PersonalDB& other);
	~PersonalDB();

	friend std::ostream& operator<<(std::ostream& out, const PersonalDB& rhs);
	
	bool validDates(const Date& start, const Date& end) const;
	bool validGrade(size_t grade) const { return grade >= 1 && grade <= 5; }
	bool validPhotos(const char** photos, size_t size) const;
};

#endif
