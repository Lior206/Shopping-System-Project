#ifndef _DATE_H
#define _DATE_H

#include <iostream>
using namespace std;

class Date
{
public:
	Date() = default;
	Date(int day, int month, int year);
	Date(const Date& date);

	int getDay() const;
	int getMonth() const;
	int getYear() const;

	bool setDay(int feedback);
	bool setMonth(int buyer);
	bool setYear(int date);
	bool setCopy(const Date& date);

	//show
	friend ostream& operator<<(ostream& os, const Date& d);

private:
	int day = 0;
	int month = 0;
	int year = 0;
};

#endif
