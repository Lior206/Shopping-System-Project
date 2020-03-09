#ifndef _ADDRESS_H
#define _ADDRESS_H

#include <iostream>
#include <fstream>
using namespace std;

class Address
{
public:
	//c'tors and d'tor
	Address() = default;
	Address(const string& countryName, const string& cityName, const string& streetName, int houseNum);
	Address(const Address& other);
	

	//getters and setters
	const string& getCountryName() const;
	const string& getCityName() const;
	const string& getStreetName() const;
	int getHouseNum() const;

	bool setCountryName(const string& countryName);
	bool setCityName(const string& cityName);
	bool setStreetName(const string& streetName);
	bool setHouseNum(int houseNum);
	bool setCopy(const Address& other); 

	//show
	friend ostream& operator<<(ostream& os, const Address& a);
	friend istream& operator>>(istream& is, Address& a);
private:
	string countryName;
	string cityName;
	string streetName;
	int houseNum = 0;
};

#endif
