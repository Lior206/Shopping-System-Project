#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
using namespace std;
#include "system.h"
#include "validate.h"

//c'tor
System::System()
{
	int size;
	string type, name, password, newline;
	Address as;
	ifstream infile("users.txt");
	infile >> size;
	for (int i = 0; i < size;i++)
	{
		infile >> type;
		getline(infile, newline);
		getline(infile, name);
		getline(infile, password);
		infile >> as;
		if (type == "Buyer")
			u += new Buyer(name, password, as);
		else if (type == "Seller")
			u += new Seller(name, password, as);
		else
			u += new SellerBuyer(name, password, as);
	}
	infile.close();
}
//d'tor
System::~System()
{
	writeToFile();
}

void System::writeToFile() const
{
	string newline = "\n";
	ofstream outfile("users.txt", ios::trunc);
	outfile << u.getLsize();
	for (int i = 0; i < u.getLsize();i++)
	{
		if (!Validate::isSeller(*u[i]))
			outfile << newline <<"Buyer";
		else if (!Validate::isBuyer(*u[i]))
			outfile << newline << "Seller";
		else
			outfile << newline << "BuyerSeller";
		outfile << newline << u[i]->getName() << newline << u[i]->getPassword() << newline << u[i]->getAddress();
	}
	outfile.close();
}

//getters
User** System::getUsers() const
{
	return this->u.getArr();
}

vector<Order> System::getOrders() const
{
	return this->o;
}

int System::getNumOfUsers() const
{
	return this->u.getLsize();
}

//adding seller or buyer to users array
bool System::addUser(const User& user, uType type)
{
	User* newUser;
	if (Validate::AlreadyExistUser(user, this->u, u.getLsize()))
		return false;

	switch (type)
	{//enum
	case SELLER:
		newUser = new Seller(user);
		break;
	case BUYER:
		newUser = new Buyer(user);
		break;
	default:
		newUser = new SellerBuyer(user);
		break;
	}
	this->u += newUser;
	return true;
}

//getting seller index in array
int System::getUserIndex(const string& name) const
{
	for (int i = 0; i < this->u.getLsize(); i++)
		if (name == this->u[i]->getName())
			return i;

	return -1;
}

//adding product to seller
void System::addProductToSeller(const Product& p, int indx)
{
	if (Validate::isSeller(*this->u[indx]))
	{
		Seller* temp = dynamic_cast<Seller*>(this->u[indx]);
		temp->addProduct(p);
	}
	else
	{
		cout << "Not seller in this index!";
		exit(1);
	}
}

//adding product to buyer cart
bool System::addProductToBuyerCart(int serial, int indx_buyer, int indx_seller)
{
	//validation checking and dynamic cast
	Seller* s_temp;
	Buyer* b_temp;

	if (indx_buyer == indx_seller)
	{
		cout << "\nBuyer can't add to his own cart";
		return false;
	}

	if (Validate::isSeller(*this->u[indx_seller]) && Validate::isBuyer(*this->u[indx_buyer]))
	{
		s_temp = dynamic_cast<Seller*>(this->u[indx_seller]);
		b_temp = dynamic_cast<Buyer*>(this->u[indx_buyer]);
	}
	else
		return false;
	
	for (int i=0;i<s_temp->getProductsSize(); i++)
	{
		if (serial == s_temp->getProducts()[i]->getSerialNumber())
		{
			b_temp->addProductToCart(*s_temp->getProducts()[i]);
			return true;
		}
	}
	return false;
}

//check if product is in buyers cart
bool System::isExistInBuyer(int indx_buyer, int serial) const
{
	//validation checking and dynamic cast
	Buyer* b_temp;
	if (Validate::isBuyer(*this->u[indx_buyer]))
		b_temp = dynamic_cast<Buyer*>(this->u[indx_buyer]);
	else
		return false;
	for (int i=0;i< b_temp->getCartSize();i++)
		if (b_temp->getCart()[i]->getSerialNumber() == serial)
			return true;
	return false;
}

//create order for buyer
bool System::createOrderForBuyer(int indx_buyer, vector<int> serials)
{
	//validation checking and dynamic cast
	Buyer* b_temp;
	if (Validate::isBuyer(*this->u[indx_buyer]))
		b_temp = dynamic_cast<Buyer*>(this->u[indx_buyer]);
	else
		return false;
	Order o;
	vector<Product*> p;
	vector<Seller> s;
	//loop to run on buyers cart
	for (int i=0;i< b_temp->getCartSize();i++)
		for (int j=0; j< serials.size();j++) //loop to run on serials array
			if (b_temp->getCart()[i]->getSerialNumber() == serials[j])
			{
				p.push_back(new Product(*b_temp->getCart()[i]));
				s.push_back(Seller(b_temp->getCart()[i]->getSeller()));
			}
	o.setBuyer(*b_temp);
	o.setSellers(s);
	o.setProducts(p);
	for (int i=0; i< p.size();i++)
		delete p[i];
	s.clear();
	p.clear();
	this->o.push_back(o);
	return true;
}

//chaeck if buyer has an open order
int System::hasActiveOrder(const string& buyer_name) const
{
	for (int i=0; i< this->o.size();i++)
		if (this->o[i].getBuyer().getName() == buyer_name && !this->o[i].getPayState())
			return i;
	return -1;
}

//closing order for buyer
bool System::closeOrderForBuyer(int buyer_indx, int order_indx)
{
	//validation checking and dynamic cast
	Buyer* b_temp;
	if (Validate::isBuyer(*this->u[buyer_indx]))
		b_temp = dynamic_cast<Buyer*>(this->u[buyer_indx]);
	else
		return false;

	this->o[order_indx].closeOrder();
	vector<Product*> newCart;
	bool InOrder;
	
	
	//loop to run on buyers cart
	for (int i=0; i< b_temp->getCartSize(); i++)
	{
		InOrder = false;
		//loop to determine if buyer's product in the order
		for (int j=0; j< o[order_indx].getProNum(); j++)
			if (b_temp->getCart()[i]->getSerialNumber() == o[order_indx].getProducts()[j]->getSerialNumber())
			{
				InOrder = true;
				break;
			}
		if (!InOrder)
		{
			//adding the product to buyers cart if the product not in the order
			newCart.push_back(new Product(*b_temp->getCart()[i]));
		}
	}
	b_temp->setCart(newCart);	
	for (int i=0;i < newCart.size();i++)
		delete newCart[i];
	newCart.clear();
	return true;
}

//check the history of orders for spesific buyer and seller
bool System::hadClosedOrder(int buyer_indx, int seller_indx) const
{
	//pointers for dynamic cast
	Seller* s_temp;
	Buyer* b_temp;
	if (buyer_indx == seller_indx)
	{
		cout << "\nBuyer can't add to his own cart";
		return false;
	}
	//validation checking and dynamic cast
	if (Validate::isSeller(*this->u[seller_indx]) && Validate::isBuyer(*this->u[buyer_indx]))
	{
		s_temp = dynamic_cast<Seller*>(this->u[seller_indx]);
		b_temp = dynamic_cast<Buyer*>(this->u[buyer_indx]);
	}
	else
		return false;
	//loop to run on order history
	for (int i=0;i < o.size(); i++)
		if (o[i].getBuyer().getName() == b_temp->getName())
			for (int j = 0; j < o[i].getSellersNum();j++)
				if (o[i].getSellers()[j].getName() == s_temp->getName())
					if (o[i].getPayState())
						return true;
	return false;
}

//adding feedback to seller
bool System::addFeedbackToSeller(const string& buffer, int buyer_indx, int seller_indx, const Date& d)
{
	//two pointers for dynamic cast
	Seller* s_temp;
	Buyer* b_temp;

	if (buyer_indx == seller_indx)
	{
		cout << "\nBuyer can't add feedback to himself!";
		return false;
	}
	//validation checking and dynamic cast
	if (Validate::isSeller(*this->u[seller_indx]) && Validate::isBuyer(*this->u[buyer_indx]))
	{
		s_temp = dynamic_cast<Seller*>(this->u[seller_indx]);
		b_temp = dynamic_cast<Buyer*>(this->u[buyer_indx]);
	}
	else
		return false;
	s_temp->addFeedback(*b_temp, d, buffer);
	return true;
}

//2
bool System::operator+=(const Seller& s)
{
	return this->addUser(s, SELLER);
}

//1
bool System::operator+=(const Buyer& b)
{
	return this->addUser(b, BUYER);
}

//function to campare two buyers cart
int System::hasMoreExpensive(int first_buyer, int second_buyer) const
{
	//dynamic cast for two buyers
	Buyer* b_tmp1;
	Buyer* b_tmp2;
	//validation checking and dynamic cast
	if (Validate::isBuyer(*this->u[first_buyer]) && Validate::isBuyer(*this->u[second_buyer]))
	{
		b_tmp1 = dynamic_cast<Buyer*>(this->u[first_buyer]);
		b_tmp2 = dynamic_cast<Buyer*>(this->u[second_buyer]);
	}
	else
		return -1;
	//using operator function >
	if (b_tmp1->getCartAmou() == b_tmp2->getCartAmou())
		return -2;
	else if (*b_tmp1 > *b_tmp2)
		return first_buyer;
	else
		return second_buyer;
}