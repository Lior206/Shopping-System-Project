#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

#include "user.h"
#include "validate.h"
//c'tors 
User::User(const string& name, const string& password, const Address& address)
{
	this->setName(name);
	this->setAddress(address);
	this->setPassword(password);
}

User::User(const User& other)
{
	*this = other;
}


//getters
const string& User::getName() const
{
	return this->name;
}

const Address& User::getAddress() const
{
	return this->address;
}

const string& User::getPassword() const
{
	return this->password;
}


//setters
bool User::setName(const string& name)
{
	if (Validate::name(name))
	{
		this->name = name;
		return true;
	}
	else
		return false;
}

bool User::setAddress(const Address& address)
{
	return this->address.setCopy(address);
}

bool User::setPassword(const string& password)
{
	if (Validate::password(password))
	{
		this->password = password;
		return true;
	}
	else
		return false;
}

bool User::operator=(const User& other)
{
	return this->setName(other.getName()) &&
		this->setPassword(other.getPassword()) &&
		this->setAddress(other.getAddress());
}

//show function
void User::show() const
{
	cout << "\n\nName:" << name << "\nPassword:" << password;
	cout << address;
}

