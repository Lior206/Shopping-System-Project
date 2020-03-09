#include <iostream>
using namespace std;
#include "sellerbuyer.h"
#include "validate.h"

SellerBuyer::SellerBuyer(const string& name, const string& password, const Address& address) : User(name, password, address)
{
}

SellerBuyer::SellerBuyer(const User& u) :User(u), Seller(u), Buyer(u)
{
}

void SellerBuyer::show() const
{
	User::show();
	if (cart.size() == 0)
		cout << "\nNo Products in cart";
	else
	{
		cout << "\nProducts in cart:";
		for (int i=0;i < cart.size();i++)
			cart[i]->show();
	}

	if (fb.size() == 0)
		cout << "\nNo Feedbacks";
	else
	{
		cout << "\nFeedbacks:";
		for (int i=0; i< fb.size(); i++)
				cout << fb[i];
	}
	if (pro.size() == 0)
		cout << "\nNot selling any products";
	else
	{
		cout << "\nSell Products:";
		for (int i=0; i< pro.size(); i++)
			pro[i]->show();
	}
}
bool SellerBuyer:: operator=(const SellerBuyer& sb)
{
	return (((Seller&)*this = (Seller&)sb) && ((Buyer&)*this = (Buyer&)sb));
}

User* SellerBuyer::clone() const {
	User* res;
	res = new SellerBuyer(*this);
	Validate::dynamicAlloc(res);
	return res;
}