#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

#include "validate.h"
#include "Array.h"

//checking string is a valid name
bool Validate::name(const string& name)
{
	int size = name.size();
	int i;

	if (size < 2)
		return false;
	else
	{
		for (i = 0; i < size; i++) {
			if ((name[i]<'a' || name[i]>'z') && (name[i]<'A' || name[i]>'Z') && (name[i] != ' '))
				return false;
		}
		return true;
	}
}
//checking the number isnt negative
bool Validate::intNumber(int num)
{
	return num >= 0;
}
//validate day value
bool Validate::day(int num)
{
	return (num > 0) && (num < 32);
}
//validate month value
bool Validate::month(int num)
{
	return (num > 0) && (num < 13);
}
//checking double number isnt negative
bool Validate::doubNumber(double num)
{
	return num > 0;
}
//checking review is not empty
bool Validate::review(const string& str)
{
	return str.size() > 0;
}
//password should have at least 8 symbles contain numbers
bool Validate::password(const string& str)
{
	int size = str.size();
	bool theresNumber = false;
	int i;
	if (size < 8)
		return false;
	else
	{
		for (i = 0; i < size; i++)
		{
			if (str[i] == ' ')
				return false;
			else if (str[i] >= '1' && str[i] <= '9')
				theresNumber = true;
		}

		return theresNumber;
	}
}
//generic function to check memory allocation
void Validate::dynamicAlloc(void* pointer)
{
	if (!pointer)
	{
		cout << "Allocation faild!";
		exit(-1);
	}
}
//checking if seller is already exist
bool Validate::AlreadyExistUser(const User& u, Array<User>& arr, int arrSize)
{
	for (int i = 0; i < arrSize; i++)
		if (arr[i]->getName() == u.getName())
			return true;
	return false;
}

bool Validate::isSeller(const User& u)
{
	return typeid(u) != typeid(Buyer);
}

bool Validate::isBuyer(const User& u)
{
	return typeid(u) != typeid(Seller);
}