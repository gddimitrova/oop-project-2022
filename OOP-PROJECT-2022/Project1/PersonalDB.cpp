#include "PersonalDB.h"
#define DEFAULT_CAP 8

void PersonalDB::copyFrom(const char** photos, size_t size)
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

PersonalDB::PersonalDB(const char* destination, int day, int month, int year, int dayEnd, int monthEnd, int yearEnd, size_t grade, const char* comment, const char** photos, size_t size)
	:mDestination(destination), mComment(comment), mCapacity(DEFAULT_CAP)
{
	Date start(year, month, day), end(yearEnd, monthEnd, dayEnd);

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

bool PersonalDB::validDates(const Date& start, const Date& end) const
{
	return (start.getYear() <= end.getYear()) &&
			((start.getDay() <= end.getDay() && start.getMonth() <= end.getMonth()) ||
			(start.getDay() > end.getDay() && start.getMonth() < end.getMonth()) ||
			(start.getDay() <= end.getDay() && start.getMonth() > end.getMonth() && start.getYear() < end.getYear()) ||
			(start.getDay() > end.getDay() && start.getMonth() > end.getMonth() && start.getYear() < end.getYear()));

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

bool PersonalDB::validPhotos(const char** photos, size_t size) const
{
	for (size_t i = 0; i < size; i++) {
		if (!validExtension(photos[i]))
			return false;
	}

	return true;
}

std::ostream& operator<<(std::ostream& out, const PersonalDB& rhs)
{
	out << "Destination:" << rhs.mDestination << std::endl;
	out << "Time period:" << rhs.mStart << " - " << rhs.mEnd << std::endl;
	out << "Grade:" << rhs.mGrade << std::endl;
	out << "Comment:" << rhs.mComment << std::endl;
	out	<< "Photos:";
	for (size_t i = 0; i < rhs.mSize; i++) {
		out << rhs.mPhotos[i] << " ";
	}

	return out;
}