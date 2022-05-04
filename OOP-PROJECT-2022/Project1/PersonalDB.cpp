#include "PersonalDB.h"

void PersonalDB::copyFrom(const char** photos, size_t size, size_t capacity)
{
	mSize = size;
	mCapacity = capacity;

	mPhotos = new MyString[capacity + 1];
	for (size_t i = 0; i < mSize; i++) {
		mPhotos[i] = photos[i];
	}
}

void PersonalDB::copyFromOther(const PersonalDB& other)
{
	mSize = other.mSize;
	mCapacity = other.mCapacity;

	mPhotos = new MyString[mCapacity];
	for (size_t i = 0; i < mSize; i++) {
		mPhotos[i] = other.mPhotos[i];
	}
}

void PersonalDB::free()
{
	delete[] mPhotos;
}

PersonalDB::PersonalDB(const char* destination, int day, int month, int year, int dayEnd, int monthEnd, int yearEnd, size_t grade, const char* comment, const char** photos, size_t size)
	:mDestination(destination), mStart(year,month, day), mEnd(yearEnd, monthEnd, dayEnd), mGrade(grade), mComment(comment)
{
	copyFrom(photos, size, mCapacity);
}

PersonalDB::PersonalDB(const PersonalDB& other)
	: mDestination(other.mDestination), mStart(other.mStart), mEnd(other.mEnd), mGrade(other.mGrade), mComment(other.mComment)
{
	copyFromOther(other);
}

PersonalDB& PersonalDB::operator=(const PersonalDB& other)
{
	if (this != &other) {
		free();
		copyFromOther(other);
	}

	return *this;
}

PersonalDB::~PersonalDB()
{
	free();
}
