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

	void copyFrom(char** photos, size_t size);
	void copyFromOther(const PersonalDB& other);
	void free();
	void resize(size_t newSize);

public:
	PersonalDB(size_t capacity);
	PersonalDB(const char* destination = nullptr, const Date& start=Date(1,1,1), const Date& end=Date(1,1,1), size_t grade = 1, const char* comment = nullptr,char** photos = nullptr, size_t size = 0);
	PersonalDB(const PersonalDB& other);
	PersonalDB& operator=(const PersonalDB& other);
	~PersonalDB();

	friend std::ostream& operator<<(std::ostream& out, const PersonalDB& rhs);
	
	void readFromFile(std::ifstream& inFile);
	//void writeToFile(const char* filename);
	
	bool validDates(const Date& start, const Date& end) const;
	bool validGrade(size_t grade) const { return grade >= 1 && grade <= 5; }
	bool validPhotos(char** photos, size_t size) const;

	void setDestination(const char* destination);
	void setStart(const Date& start);
	void setEnd(const Date& end);
	void setGrade(size_t grade);
	void setPhotos(char** photos, size_t size);
	void setComment(const char* comment) { mComment = comment; }

	const MyString getDestination() const { return mDestination; }
};

#endif

