#define _CRT_SECURE_NO_WARNINGS

#include "date.h"
#include "validate.h"
//c'tors
Date::Date(int day, int month, int year)
{
	this->setDay(day);
	this->setMonth(month);
	this->setYear(year);
}

Date::Date(const Date& date)
{
	this->setCopy(date);
}

//getters
int Date::getDay() const
{
	return this->day;
}

int Date::getMonth() const
{
	return this->month;
}

int Date::getYear() const
{
	return this->year;
}


//setters
bool Date::setDay(int day)
{
	if (Validate::day(day))
	{
		this->day = day;
		return true;
	}

	else
		return false;
}

bool Date::setMonth(int month)
{
	if (Validate::month(month))
	{
		this->month = month;
		return true;
	}

	else
		return false;
}

bool Date::setYear(int year)
{
	if (Validate::intNumber(year))
	{
		this->year = year;
		return true;
	}

	else
		return false;
}

bool Date::setCopy(const Date& date)
{
	return this->setDay(date.getDay()) &&
		this->setMonth(date.getMonth()) &&
		this->setYear(date.getYear());
}

//show
ostream& operator<<(ostream& os, const Date& d)
{
	os << d.day << "/" << d.month << "/" << d.year;
	return os;
}