#ifndef _SELLER_H
#define _SELLER_H

#include "user.h"
#include "product.h"
#include "feedback.h"
#include <vector>
#include <algorithm>

class Seller : virtual public User {
public:
	//c'tors and d'tor
	Seller() = default;
	Seller(const string& name, const string& password, const Address& address);
	Seller(const User& user);
	Seller(const Seller& other);
	
	//getters
	vector<Product*> getProducts() const;
	const vector<Feedback> getFeedbacks() const;
	int getFeedbacksSize() const;
	int getProductsSize() const;

	//setters
	virtual bool operator=(const Seller& other);

	//show 
	virtual void show() const override;
	
	//add
	void addProduct(const Product& p);
	void addFeedback(const Buyer& b, const Date& d, const string& review);
	virtual User* clone() const override;

protected:
	vector<Product*> pro;
	vector<Feedback> fb;
};
#endif