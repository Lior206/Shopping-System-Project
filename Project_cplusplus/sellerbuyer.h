#ifndef _SELLERBUYER_H
#define _SELLERBUYER_H

#include "seller.h"
#include "buyer.h"

class SellerBuyer : public Seller, public Buyer
{
public:

	SellerBuyer() = default;
	SellerBuyer(const string& name, const string& password, const Address& address);
	SellerBuyer(const User& u);

	//show
	virtual void show() const override;
	bool operator=(const SellerBuyer& sb);

	virtual User* clone() const override;
};
#endif
