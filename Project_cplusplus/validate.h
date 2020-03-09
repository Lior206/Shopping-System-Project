#ifndef _VALIDATE_H
#define _VALIDATE_H

#include "user.h"
#include "seller.h"
#include "buyer.h"
#include "sellerbuyer.h"
#include <string>
#include <vector>
template<class T>
class Array;

//class to check validation for arrtibutes
class Validate
{
public:
	static bool name(const string& str);
	static bool intNumber(int num);
	static bool day(int num);
	static bool month(int num);
	static bool doubNumber(double num);
	static bool password(const string& str);
	static bool review(const string& str);
	static void dynamicAlloc(void* pointer);
	static bool AlreadyExistUser(const User& u, Array<User>& arr, int arrSize);
	static bool isSeller(const User& u);
	static bool isBuyer(const User& u);
};
#endif // !_VALIDATE_H