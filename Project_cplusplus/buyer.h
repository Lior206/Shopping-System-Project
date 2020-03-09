#ifndef _BUYER_H
#define _BUYER_H

#include "user.h"
#include "product.h"
#include <vector>

class Buyer :virtual public User
{
public:
	//c'tors and d'tor
	Buyer() = default;
	Buyer(const string& name, const string& password, const Address& address);
	Buyer(const User& other);
	Buyer(const Buyer& other);

	//getter's and setter's
	int getCartSize() const;
	double getCartAmou() const;
	vector<Product*> getCart() const;

	virtual bool operator=(const Buyer& other);
	bool operator>(const Buyer& other);
	bool setCart(vector<Product*> cart);
	void addProductToCart(const Product& p);

	//show =
	virtual void show() const override;
	virtual User* clone() const override;

protected:
	vector<Product*> cart;
};

#endif
