#ifndef DATE_H_INCLUDED
#define DATE_H_INCLUDED

class Date
{
private:
	int mDay;
	int mMonth;
	int mYear;

public:
	Date();
	Date(int year, int month, int day);
};

#endif
