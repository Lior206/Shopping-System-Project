#ifndef _PRODUCT_H
#define _PRODUCT_H

class Seller;
enum eCategory { CHILDREN, ELECTRONICS, OFFICE, CLOTHING };

class Product
{
public:
	//c'tors and d'tor
	Product(const Seller& seller);
	Product(const string& name, double price, eCategory category, const Seller& seller);
	Product(const Product& other);
	
	//getters
	const string& getName() const;
	double getPrice() const;
	int getSerialNumber() const;
	eCategory getCategory() const;
	const Seller& getSeller() const;

	//setters
	bool setName(const string& name);
	bool setPrice(double price);
	bool setCategory(eCategory category);
	bool setSerial(int num);
	bool operator=(const Product& other);

	//show
	void show() const;


private:
	string name;
	double price = 0;
	static int counter;
	int serial = 0;
	eCategory category = (eCategory)0;
	const Seller& s;
};
#endif