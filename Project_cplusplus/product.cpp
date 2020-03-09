#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

#include "product.h"
#include "validate.h"
#include "seller.h"
const char* categories[] = { "Children","Electronics","Office","Clothing" };
int Product::counter = 0;

//c'tors
Product::Product(const Seller& seller) : s(seller)
{
	this->price = 0;
	this->category = (eCategory)0;
	this->name;
	serial = ++counter;
}


Product::Product(const string& name, double price, eCategory category,const Seller& seller) : s(seller)
{
	this->setName(name);
	this->setPrice(price);
	this->setCategory(category);
	serial = ++counter;
}

Product::Product(const Product& other) : s(other.s)
{
	*this = other;
}


//getters
const string& Product::getName() const
{
	return this->name;
}

double Product::getPrice() const
{
	return this->price;
}

int Product::getSerialNumber() const
{
	return this->serial;
}

eCategory Product::getCategory() const
{
	return this->category;
}

const Seller& Product::getSeller() const
{
	return this->s;
}

//setters
bool Product::setName(const string& name)
{
	if (!Validate::name(name))
		return false;
	else
	{
		this->name = name;
		return true;
	}

}

bool Product::setPrice(double price)
{
	if (!Validate::doubNumber(price))
		return false;
	else
	{
		this->price = price;
		return true;
	}
}

bool Product::setCategory(eCategory category)
{
	bool res = true;

	switch (category)
	{
	case 0:
		this->category = CHILDREN;
		break;
	case 1:
		this->category = ELECTRONICS;
		break;
	case 2:
		this->category = OFFICE;
		break;
	case 3:
		this->category = CLOTHING;
		break;
	default:
		res = false;
	}

	return res;
}

bool Product::setSerial(int num)
{
	if (!Validate::intNumber(num))
		return false;
	else
	{
		this->serial = num;
		return true;
	}
}

bool Product::operator=(const Product& other)
{
	return this->setName(other.getName()) &&
		this->setPrice(other.getPrice()) &&
		this->setSerial(other.getSerialNumber()) &&
		this->setCategory(other.getCategory());
}

//show function
void Product::show() const
{
	cout << "\nName: " << this->name;
	cout << "\nPrice: " << this->price;
	cout << "\nSerial Number: " << this->serial;
	cout << "\nCategory: " << categories[this->category];
	cout << "\nSeller:" << this->s.getName();
}