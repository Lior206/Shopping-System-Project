#define _CRT_SECURE_NO_WARNINGS

#include "address.h"
#include "validate.h"

//c'tors
Address::Address(const string& countryName, const string& cityName, const string& streetName, int houseNum)
{
	this->setCountryName(countryName);
	this->setCityName(cityName);
	this->setStreetName(streetName);
	this->setHouseNum(houseNum);
}
Address::Address(const Address& other)
{
	this->setCopy(other);
}


//getters and setters
const string& Address::getCountryName() const
{
	return this->countryName;
}

const string& Address::getCityName() const
{
	return this->cityName;
}
const string& Address::getStreetName() const
{
	return this->streetName;
}
int Address::getHouseNum() const
{
	return this->houseNum;
}

bool Address::setCountryName(const string& countryName)
{
	if (Validate::name(countryName))
	{
		this->countryName = countryName;
		return true;
	}
	else
		return false;
}
bool Address::setCityName(const string& cityName)
{
	if (Validate::name(cityName))
	{
		this->cityName = cityName;
		return true;
	}
	else
		return false;
}
bool Address::setStreetName(const string& streetName)
{
	if (Validate::name(streetName))
	{
		this->streetName = streetName;
		return true;
	}
	else
		return false;
}
bool Address::setHouseNum(int houseNum)
{
	if (Validate::intNumber(houseNum))
	{
		this->houseNum = houseNum;
		return true;
	}
	else
		return false;
}

bool Address::setCopy(const Address& other)
{
	return this->setCountryName(other.getCountryName()) &&
		this->setCityName(other.getCityName()) &&
		this->setStreetName(other.getStreetName()) &&
		this->setHouseNum(other.getHouseNum());
}

//show
ostream& operator<<(ostream& os, const Address& a)
{
	string newline = "\n";
	if (typeid(os) == typeid(ofstream))
		os << a.countryName << newline << a.cityName << newline << a.streetName << newline << a.houseNum;
	else
	{
		os << "\nAddress:\n";
		os << a.countryName;
		os << newline << a.cityName;
		os << newline << a.streetName << " " << a.houseNum;
	}
	return os;
}

istream& operator>>(istream& is, Address& a)
{
	getline(is, a.countryName);
	getline(is, a.cityName);
	getline(is, a.streetName);
	is >> a.houseNum;
	return is;
}