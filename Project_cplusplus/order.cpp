#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

#include "order.h"
#include "validate.h"

//c'tors
Order::Order(const Buyer& buyer, const vector<Seller> seller,const vector<Product*> products) :buyer(buyer)
{
	if (this->setProducts(products) && this->setSellers(seller))
		this->setPrice();
}

Order::Order(const Order& order)
{
	*this = order;
}

//getter's
const Buyer& Order::getBuyer() const
{
	return this->buyer;
}

vector<Seller> Order::getSellers() const
{
	return this->sellers;
}

vector<Product*> Order::getProducts() const
{
	return this->products;
}

int Order::getProNum() const
{
	return this->products.size();
}

int Order::getSellersNum() const
{
	return this->sellers.size();
}

double Order::getPrice() const
{
	return this->price;
}

//setter's
bool Order::setBuyer(const Buyer& buyer)
{
	return this->buyer = buyer;
}

bool Order::setSellers(vector<Seller> seller)
{
	copy(seller.begin(), seller.end(), back_inserter(this->sellers));
	return true;
}

bool Order::setProducts(vector<Product*> products)
{
	for (int i=0;i < products.size(); i++)
		this->products.push_back(new Product(*products[i]));
	return true;
}

//seting the price as the sum of prices of the order's product
bool Order::setPrice()
{
	double res = 0;
	
	for (int i=0;i < products.size(); i++)
		res += products[i]->getPrice();
	
	if (Validate::doubNumber(res))
	{
		this->price = res;
		return true;
	}
	else
	{
		this->price = 0;
		return false;
	}
}

bool Order::operator=(const Order& order)
{
	if (this->setBuyer(order.getBuyer()) &&
		this->setSellers(order.getSellers()) &&
		this->setProducts(order.getProducts()))
		return this->setPrice();
	else
		return false;
}

bool Order::getPayState() const
{
	return this->isPaid;
}

void Order::closeOrder()
{
	this->isPaid = true;
}