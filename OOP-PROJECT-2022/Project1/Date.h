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

	bool isValidDate(int day, int month, int year) const;

};

#endif
