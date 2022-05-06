#ifndef DATE_H_INCLUDED
#define DATE_H_INCLUDED
#include <fstream>

class Date
{
private:
	int mDay;
	int mMonth;
	int mYear;

public:
	Date();
	Date(int year, int month, int day);
	
	friend std::ostream& operator<<(std::ostream& out, const Date& rhs);
	friend std::istream& operator>>(std::istream& in, Date& rhs);

	bool isValidDate(int day, int month, int year) const;

	int getDay() const { return mDay; }
	int getMonth() const { return mMonth; }
	int getYear() const { return mYear; }

	void setDay(int day) { mDay = day; }
	void setMonth(int month) { mMonth = month; }
	void setYear(int year) { mYear = year; }

};

#endif
