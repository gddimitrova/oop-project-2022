#include "PersonalDB.h"
#include <iostream>
#define DEFAULT_CAP 8
#define MAX_LEN 2048

void PersonalDB::copyFrom(char** photos, size_t size)
{
	resize(size);

	mSize = size;

	mPhotos = new MyString[mCapacity];
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

void PersonalDB::resize(size_t newSize)
{
	bool needErase = false;
	if ((mCapacity * 3) / 4 <= newSize) {
		mCapacity *= 2;
		needErase = true;
	}
	if (mCapacity / 4 >= newSize) {
		mCapacity /= 2;
		needErase = true;
	}
	if (needErase) {
		MyString* save = mPhotos;
		mPhotos = new MyString[mCapacity];
		for (size_t i = 0; i < mSize; i++) {
			mPhotos[i] = save[i];
		}
		delete[] save;
	}
}

PersonalDB::PersonalDB(size_t capacity)
	:mDestination(nullptr), mStart(1,1,1),mEnd(1,1,1),mGrade(1),mComment(nullptr),mSize(0),mCapacity(capacity)
{
	mPhotos = new MyString[mCapacity];
}

PersonalDB::PersonalDB(const char* destination, const Date& start, const Date& end, size_t grade, const char* comment,char** photos, size_t size)
	:mDestination(destination),mComment(comment), mCapacity(DEFAULT_CAP)
{

	if (!validDates(start, end))
		throw std::exception("Invalid dates!");
	mStart = start;
	mEnd = end;

	if (!validGrade(grade))
		throw std::exception("Invalid grade!");
	mGrade = grade;

	if (!validPhotos(photos, size)) {
		throw std::exception("Invalid photo format!");
	}
	copyFrom(photos, size);
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

void PersonalDB::readFromFile(std::ifstream& inFile)
{

	inFile.ignore(13);
	inFile >> mDestination;
	inFile.ignore(14);
	inFile >> mStart;
	inFile.ignore(3);
	inFile >> mEnd;
	inFile.ignore(8);
	inFile >> mGrade;
	inFile.ignore(10);
	inFile >> mComment;
	
	inFile.ignore(11);
	size_t size;
	inFile >> size;
	
	mSize = size;

	inFile.ignore(9);
	for (size_t i = 0; i < mSize; i++) {
		inFile >> mPhotos[i];
		if (i < mSize - 1) {
			inFile.ignore();
		}
	}
}


bool PersonalDB::validDates(const Date& start, const Date& end) const
{
	if (start.getYear()> end.getYear()) {
		return false;
	}
	if (start.getYear() < end.getYear()) {
		return true;
	}

	if (start.getMonth() > end.getMonth()) {
		return false;
	}
	if (start.getMonth() < end.getMonth()) {
		return true;
	}

	if (start.getDay() > end.getDay()) {
		return false;
	}
	if (start.getDay() < end.getDay()) {
		return true;
	}

	return true;

	/*return (start.getYear() <= end.getYear()) &&
		((start.getDay() <= end.getDay()) && (start.getMonth() <= end.getMonth())) ||
		((start.getDay() > end.getDay()) && (start.getMonth() < end.getMonth())) ||
		((start.getDay() <= end.getDay()) && (start.getMonth() > end.getMonth()) && (start.getYear() < end.getYear())) ||
		((start.getDay() > end.getDay()) && (start.getMonth() > end.getMonth()) && (start.getYear() < end.getYear()));*/
}

bool validExtension(const char* photo) {
	int i = 0;
	while (photo[i] != '\0') {
		if (photo[i] == '.') {
			i++;
			return (strcmp((photo + i), "jpeg") == 0) || (strcmp((photo + i), "png") == 0);
		}
		if (!(isalpha(photo[i]) || photo[i] == '_') || photo[i] == ' ') {
			return false;
		}
		i++;
	}

	return false;
}

bool PersonalDB::validPhotos(char** photos, size_t size) const
{
	for (size_t i = 0; i < size; i++) {
		if (!validExtension(photos[i]))
			return false;
	}

	return true;
}

void PersonalDB::setDestination(const char* destination)
{
	mDestination = destination;
}

void PersonalDB::setStart(const Date& start)
{
	mStart = start;
}

void PersonalDB::setEnd(const Date& end)
{
	mEnd = end;
}

void PersonalDB::setGrade(size_t grade)
{
	if (!validGrade(grade))
		throw std::exception("Invalid grade!");
	mGrade = grade;
}

void PersonalDB::setPhotos(char** photos, size_t size)
{
	if (!validPhotos(photos, size)) {
		throw std::exception("Invalid photo format!");
	}
	copyFrom(photos, size);
}

std::ostream& operator<<(std::ostream& out, const PersonalDB& rhs)
{
	bool isCout = (&out == &std::cout);
	out << "Destination: ";
	(isCout) ? out << rhs.mDestination.getString() : out << rhs.mDestination;
	out << std::endl;
	out << "Time period: " << rhs.mStart << " - " << rhs.mEnd << std::endl;
	out << "Grade: " << rhs.mGrade << std::endl;
	out << "Comment: ";
	(isCout) ? out << rhs.mComment.getString() : out << rhs.mComment;
	out << std::endl;
	out << "There are " << rhs.mSize << " photos: ";
	for (size_t i = 0; i < rhs.mSize; i++) {
		(isCout) ? out << rhs.mPhotos[i].getString() : out << rhs.mPhotos[i];
		if (i < rhs.mSize - 1) {
			out << " ";
		}
	}
	out << std::endl;

	return out;
}