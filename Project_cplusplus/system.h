#ifndef _SYSTEM_H
#define _SYSTEM_H

#include "sellerbuyer.h"
#include "order.h"
#include "Array.h"

enum uType { BUYER, SELLER, SELLERBUYER };
//A class for all important operation
class System {
public:

	//c'tors and d'tor
	System();
	~System();
	//system operation function
	void writeToFile() const;
	User** getUsers() const;
	vector<Order> getOrders() const;
	int getNumOfUsers() const;
	int getUserIndex(const string& name) const;
	bool isExistInBuyer(int indx_buyer, int serial) const;
	int hasActiveOrder(const string& buyer_name) const;
	int hasMoreExpensive(int first_buyer, int second_buyer) const;
	bool hadClosedOrder(int buyer_indx, int seller_indx) const;
	bool addUser(const User& u, uType type);
	void addProductToSeller(const Product& p, int indx);
	bool addProductToBuyerCart(int serial, int indx_buyer, int indx_seller);
	bool createOrderForBuyer(int indx_buyer, vector<int> serials);
	bool closeOrderForBuyer(int buyer_indx, int order_indx);
	bool addFeedbackToSeller(const string& buffer,int buyer_indx, int seller_indx, const Date& d);
	bool operator+=(const Seller& s);
	bool operator+=(const Buyer& b);
	
private:
	Array<User> u;
	vector<Order> o;
};
#endif