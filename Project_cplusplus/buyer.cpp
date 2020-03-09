#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

#include "buyer.h"
#include "validate.h"

//c'tors 
Buyer::Buyer(const string& name, const string& password, const Address& address) : User(name, password, address)
{
}
//c'tors 
Buyer::Buyer(const User& other) : User(other)
{
}

Buyer::Buyer(const Buyer& other) : User(other)
{
	*this = other;
}


//getter's

int Buyer::getCartSize() const
{
	return this->cart.size();
}

vector<Product*> Buyer::getCart() const
{
	return this->cart;
}

//setter's

bool Buyer::operator=(const Buyer& other)
{
	for (int i = 0; i<other.getCartSize(); i++)
		this->cart.push_back(new Product(*other.getCart()[i]));
	
	(User&)(*this) = (User&)other;
	return true;
}

bool Buyer::setCart(vector<Product*> cart)
{
	for (int i=0; i < this->cart.size();i++)
		delete this->cart[i];
	this->cart.clear();
	
	for (int i=0; i < cart.size(); i++)
		this->cart.push_back(new Product(*cart[i]));
	return true;
}

void Buyer::show() const
{
	if (typeid(*this) != typeid(SellerBuyer))
		User::show();

	if (cart.size() == 0)
		cout << "\nNo Products in cart";
	else
	{
		cout << "\nProducts in cart:";
		for (int i=0;i < cart.size();i++)
			this->cart[i]->show();
	}
}
//function to add product to buyer's cart
void Buyer::addProductToCart(const Product& p)
{
	this->cart.push_back(new Product(p));
}

User* Buyer::clone() const {
	User* res;
	res = new Buyer(*this);
	Validate::dynamicAlloc(res);
	return res;
}

bool Buyer::operator>(const Buyer& other)
{
	if (this->getCartAmou() > other.getCartAmou())
		return true;
	else
		return false;
}

double Buyer::getCartAmou() const
{
	double res = 0;
	for (int i =0; i < cart.size();i++)
		res += cart[i]->getPrice();
	
	return res;
}

