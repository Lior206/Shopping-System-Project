#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

#include "seller.h"
#include "validate.h"
#include "sellerbuyer.h"
//c'tors
Seller::Seller(const string& name, const string& password, const Address& address) : User(name, password, address)
{
}

Seller::Seller(const User& user) : User(user)
{
}

Seller::Seller(const Seller& other) : User(other)
{
	*this = other;
}

vector<Product*> Seller::getProducts() const
{
	return this->pro;
}

const vector<Feedback> Seller::getFeedbacks() const
{
	return this->fb;
}

int Seller::getFeedbacksSize() const
{
	return this->fb.size();
}

int Seller::getProductsSize() const
{
	return this->pro.size();
}


bool Seller::operator=(const Seller& other)
{
	copy(other.fb.begin(), other.fb.end(), back_inserter(this->fb));
	for (int i=0;i< other.getProductsSize();i++)
		this->pro.push_back(new Product(*other.getProducts()[i]));
	(User&)(*this) = (User&)other;
	return true;
}

void Seller::show() const 
{
	if (typeid(*this) != typeid(SellerBuyer))
		User::show();

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

//adding product to seller
void Seller::addProduct(const Product& p)
{
	this->pro.push_back(new Product(p));
}

//adding feedback to seller
void Seller::addFeedback(const Buyer& b, const Date& d, const string& review)
{
	this->fb.push_back(Feedback(b,d,review));
}

User* Seller::clone() const {
	User* res;
	res = new Seller(*this);
	Validate::dynamicAlloc(res);
	return res;
}