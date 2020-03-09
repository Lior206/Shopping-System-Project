#ifndef _ORDER_H
#define _ORDER_H

#include "product.h"
#include "buyer.h"
#include "seller.h"
#include <vector>
#include <algorithm>

class Order
{
public:
	Order() = default;
	Order(const Buyer& buyer, const vector<Seller> seller, const vector<Product*> products);
	Order(const Order& order);
	

	const Buyer& getBuyer() const;
	vector<Seller> getSellers() const;
	vector<Product*> getProducts() const;
	double getPrice() const;
	int getProNum() const;
	int getSellersNum() const;
	bool getPayState() const;

	bool operator=(const Order& order);
	bool setBuyer(const Buyer& buyer);
	bool setSellers(vector<Seller> sellers);
	bool setProducts(vector<Product*> products);
	bool setPrice();
	void closeOrder();

private:
	vector<Product*> products;
	vector<Seller> sellers;
	Buyer buyer;
	double price = 0;
	bool isPaid = false;
};

#endif