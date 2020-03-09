#define _CRT_SECURE_NO_WARNINGS
#include "form.h"
#include <string>
#include "validate.h"
#include <iostream>
using namespace std;

//function to get user arrtibutes
void Form::askForUser(User& u, System& s)
{
	Address ad;
	bool isAddress = false;
	string state, city, street, name, password;
	char d;
	int house;
	//input user arrtibutes
	cout << "Enter state:" << endl;
	d = getchar();
	getline(cin, state);
	cout << "Enter city:" << endl;
	getline(cin, city);
	cout << "Enter street:" << endl;
	getline(cin, street);
	cout << "Enter house number:" << endl;
	cin >> house;
	isAddress = (ad.setCountryName(state) && ad.setCityName(city) && ad.setStreetName(street) && ad.setHouseNum(house));
	if (!isAddress)
	{
		cout << "Illegal address, press Enter to try again\n";
		chooseMenu(s);
		return;
	}
	u.setAddress(ad);

	d = getchar();
	cout << "Enter name:" << endl;
	getline(cin, name);
	cout << "Enter password (at least 8 characters, 1 number and no spaces): " << endl;
	getline(cin, password);

	if (!(u.setName(name) && u.setPassword(password)))
	{
		cout << "Name or password invalid" << endl;
		chooseMenu(s);
		return;
	}
}

//2
void Form::addSeller(System& s)
{
	Seller sl;
	//getting user arrtibutes
	Form::askForUser(sl, s);
	while (!(s+=sl))//loop to check succes of the task
	{
		cout << "\nSeller already exist in the system, press Enter to try different user:" << endl;
		Form::askForUser(sl, s);
	}
}

//1
void Form::addBuyer(System& s)
{
	Buyer by;
	//getting user arrtibutes
	Form::askForUser(by, s);
	while (!(s+=by))//loop to check succes of the task
	{
		cout << "\nSeller already exist in the system, press Enter to try different user:" << endl;
		Form::askForUser(by, s);
	}
}

//print menu
void Form::printInteractiveMenu()
{
	cout << "\n";
	const string options[12] = { "Add new buyer(+=)", "Add new seller(+=)",
	"Add product to seller", "Add feedback to seller","Add product to a buyer's cart",
	"Create order for buyer","Pay order for buyer","Show all product's with a specific name",
	"Add buyer-seller user","Show all users with specific type","Compare beetween two buyers cart(>)",
	"Exit"};
	for (int i = 0; i < 12; i++)
		cout << i + 1 << ". " << options[i] << ".\n";
}

void Form::chosenMethod(System& s, int choice)
{
	//switch structure for interactive menu, calling each function in the class
	switch (choice)
	{
	case 1:
		Form::addBuyer(s);
		break;
	case 2:
		Form::addSeller(s);
		break;
	case 3:
		Form::addProductToSeller(s);
		break;
	case 5:
		Form::addProductToBuyerCart(s);
		break;
	case 4:
		Form::addFeedbackToSeller(s);
		break;
	case 6:
		Form::createOrderForBuyer(s);
		break;
	case 7:
		Form::closeOrderForBuyer(s);
		break;
	case 8:
		Form::showCertainProducts(s);
		break;
	case 9 :
		Form::addSellerBuyer(s);
		break;
	case 10:
		Form::showCertainUsersByType(s);
		break;
	case 11:
		Form::compareTwoBuyers(s);
		break;
	case 12:
		Form::exitSystem(s);
		break;
	}
}

//10
void Form::showAllBuyers(System& s)
{
	//pointer dynamic cast
	Buyer* b_temp;
	bool found = false;
	//check if there are buyers in the system
	cout << "\nSystem Buyers:";
	for (int i = 0; i < s.getNumOfUsers();i++)
		if (Validate::isBuyer(*s.getUsers()[i]))
		{
			found = true;
			b_temp = dynamic_cast<Buyer*>(s.getUsers()[i]);
			b_temp->show();
		}
	//if user not found in system
	if(!found)
	{
		cout << "\nNot Buyers in the system";
		chooseMenu(s);
		return;
	}
	chooseMenu(s);
}

//10
void Form::showAllSellers(System& s)
{
	Seller* s_temp;
	bool found = false;
	//check if there are buyers in the system
	cout << "\nSystem Sellers:";
	for (int i = 0; i < s.getNumOfUsers();i++)
		if (Validate::isSeller(*s.getUsers()[i]))
		{
			found = true;
			s_temp = dynamic_cast<Seller*>(s.getUsers()[i]);
			s_temp->show();
		}
	//if user not found in system
	if (!found)
	{
		cout << "\nNot Sellers in the system";
		chooseMenu(s);
		return;
	}
	chooseMenu(s);
}

//3
void Form::addProductToSeller(System& s)
{
	bool isExist = false, isProduct = false;
	int i, price, category;
	Seller* s_temp;
	string name, p_name;
	char d;
	
	//check if there are sellers in the system
	if (s.getNumOfUsers() == 0)
	{
		cout << "\nNo Users in the system";
		chooseMenu(s);
		return;
	}
	//input loops for validation checking
	cout << "\nPlease enter seller's name: ";
	d = getchar();
	getline(cin, name);
	i = s.getUserIndex(name);
	if(i != -1 && Validate::isSeller(*s.getUsers()[i]))
		isExist = true;
	if (!isExist)
	{
		cout << "\nSeller does not exist in system!";
		chooseMenu(s);
		return;
	}
	//dynamic cast and define his product
	s_temp = dynamic_cast<Seller*>(s.getUsers()[i]);
	Product p(*s_temp);
	//get product arrtibutes
	
	cout << "\nEnter Product's name: ";
	getline(cin, p_name);
	cout << "Enter Product's category (Children = 0, Electronics = 1, Office = 2, Clothing = 3): ";
	cin >> category;
	cout << "Enter Product's price: ";
	cin >> price;
	isProduct = p.setName(p_name) && p.setPrice(price) && p.setCategory((eCategory)category);
	if (!isProduct)
	{
		cout << "\nName or price or category is not valid";
		chooseMenu(s);
		return;
	}
	//calling system function
	s.addProductToSeller(p, i);
}

//5
void Form::addProductToBuyerCart(System& s)
{
	int i, j, serial;
	bool areExist = false, isProductForSell = false;
	string s_name, b_name;
	char d;
	//check if there are users 
	if (s.getNumOfUsers() == 0)
	{
		cout << "\nNo Users in the system";
		chooseMenu(s);
		return;
	}
	//getting input for validation checking
	cout << "\nPlease enter buyer's name: ";
	d = getchar();
	getline(cin, b_name);
	i = s.getUserIndex(b_name);
	cout << "\nPlease enter seller's name to buy from: ";
	getline(cin, s_name);
	j = s.getUserIndex(s_name);
	if (i != -1 && j != -1 && Validate::isSeller(*s.getUsers()[j]) && Validate::isBuyer(*s.getUsers()[i]))
		areExist = true;
	if (!areExist)
	{
		cout << "\nBuyer or Seller does not exist in system!";
		chooseMenu(s);
		return;
	}
	s.getUsers()[j]->show();
	cout << "\n\nEnter Product's serial number: ";
	cin >> serial;
	//calling system function
	isProductForSell = s.addProductToBuyerCart(serial, i, j);
	if (!isProductForSell)
	{
		cout << "\nCould not make process!";
		chooseMenu(s);
		return;
	}
}

//8
void Form::showCertainProducts(System& s)
{
	//check if there are Users in system
	if (s.getNumOfUsers() == 0)
	{
		cout << "\nNo Users in the system";
		chooseMenu(s);
		return;
	}

	Seller* s_temp;
	char d;
	 string name;
	//input loop to get product name
	cout << "\nEnter Product's name: ";
	d = getchar();
	getline(cin, name);
	if (!Validate::name(name))
	{
		cout << "Name is not valid";
		chooseMenu(s);
		return;
	}
	
	//loop to show certain product
	for (int i = 0; i < s.getNumOfUsers();i++)
		if (Validate::isSeller(*s.getUsers()[i]))
		{
			s_temp = dynamic_cast<Seller*>(s.getUsers()[i]);
			for (int i=0 ;i < s_temp->getProductsSize();i++)
				if (name == s_temp->getProducts()[i]->getName())
					s_temp->getProducts()[i]->show();
		}
		
	cout << "\nPress Y - to continue, N - to exit system: ";
	cin >> d;
	if (d == 'N')
		Form::exitSystem(s);
}

//6
void Form::createOrderForBuyer(System& s)
{
	//pointer for dynamic cast
	Buyer* b_temp;
	//check if there are Users in system
	if (s.getNumOfUsers() == 0)
	{
		cout << "\nNo Users in the system";
		chooseMenu(s);
		return;
	}

	int i, j, serial;
	vector<int> serials;
	bool Run = true;
	char d;
	string b_name;
	
	//validation checking
	cout << "\nPlease enter buyer's name: ";
	d = getchar();
	getline(cin, b_name);
	i = s.getUserIndex(b_name);
	j = s.hasActiveOrder(b_name);
	if (i == -1 || !Validate::isBuyer(*s.getUsers()[i]))
	{
		cout << "\nBuyer does not exist in system!";
		chooseMenu(s);
		return;
	}
	if (j != -1)
	{
		cout << "\nBuyer already has an open order in system!";
		chooseMenu(s);
		return;
	}
	//dynamic cast
	b_temp = dynamic_cast<Buyer*>(s.getUsers()[i]);
	if (b_temp->getCartSize()==0)
	{
		cout << "\nBuyer doesnt have products in his cart!";
		chooseMenu(s);
		return;
	}
	b_temp->show();
	//loop to add products to cart
	do
	{
		cout << "\n\nPlease enter product's serial number from buyer's cart:";
		cin >> serial;
		if (s.isExistInBuyer(i, serial))
		{
			serials.push_back(serial);
			cout << "\nWould you like to add more Product to the order? (Y-yes, N-no)";
			cin >> d;
			if (d == 'N')
				Run = false;
		}
		else
		{
			cout << "\nProduct does not exist in buyer's cart, please choose another";
			chooseMenu(s);
		}
			
	} while (Run);
	//calling system function
	s.createOrderForBuyer(i, serials);
}

//7
void Form::closeOrderForBuyer(System& s)
{
	string b_name;
	int i, j;
	char d;
	//check if there are Users in system
	if (s.getNumOfUsers() == 0)
	{
		cout << "\nNo Users in the system";
		chooseMenu(s);
		return;
	}

	//input loop
	cout << "\nPlease enter buyer's name: ";
	d = getchar();
	getline(cin, b_name);
	i = s.getUserIndex(b_name);
	j = s.hasActiveOrder(b_name);
	if (i == -1 || !Validate::isBuyer(*s.getUsers()[i]))
	{
		cout << "\nBuyer does not exist in system";
		chooseMenu(s);
		return;
	}
	if (j == -1)
	{
		cout << "\nBuyer doesn't have an open order in system";
		chooseMenu(s);
		return;
	}
			
	//calling system function
	if (s.closeOrderForBuyer(i, j))
	{
		//display price
		cout << "\nOrder paid! total payment: " << s.getOrders()[j].getPrice();
		cout << "\nPress Y/N (Y-back to menu, N-exit) :";
		cin >> d;
		if (d == 'N')
			Form::exitSystem(s);
	}
}
	

//4
void Form::addFeedbackToSeller(System& s)
{
	string b_name, s_name, rev;
	char d;
	int i, j, year, month, day;
	bool iLegal = false;
	//check if there are Users in system
	if (s.getNumOfUsers() == 0)
	{
		cout << "\nNo Users in the system";
		chooseMenu(s);
		return;
	}
	//get feedback arrtibutes and checking their validation

	cout << "\nPlease enter buyer's name that gives the Feedback: ";
	d = getchar();
	getline(cin, b_name);
	i = s.getUserIndex(b_name);
	cout << "\nPlease enter seller's name that get the Feedback: ";
	getline(cin, s_name);
	j = s.getUserIndex(s_name);
	if (i == -1 || !Validate::isBuyer(*s.getUsers()[i]))
		iLegal = true;
	if (j == -1 || !Validate::isSeller(*s.getUsers()[j]))
		iLegal = true;
	if (i == -1 || j == -1 || !s.hadClosedOrder(i, j))
		iLegal = true;
	if (iLegal)
	{
		cout << "Invalid input! press any key to return to menu: ";
		cin >> d;
		return;
	}
	//getting review
	cout << "\nPlease enter Feedback's review: ";
	getline(cin, rev);
	if (!Validate::review(rev))
	{
		cout << "\nFeedback must hast at least one letter!";
		chooseMenu(s);
		return;
	}
	cout << "\nPlease enter current date: ";
	cout << "\nYear: ";
	cin >> year;
	cout << "Month: ";
	cin >> month;
	cout << "Day: ";
	cin >> day;
	if (!Validate::day(day) || !Validate::month(month) || !Validate::intNumber(year))
	{
		cout << "\nDate isn't valid!";
		chooseMenu(s);
		return;
	}
	//calling system function
	if (!s.addFeedbackToSeller(rev, i, j, Date(day, month, year)))
	{
		cout << "\nCould not give feedback!";
		chooseMenu(s);
	}
}

//display menu for different situations
void Form::chooseMenu(System& s)
{
	char d;
	cout << "\nPress Y/N (Y-continue, N-exit):";
	cin >> d;
	if (d == 'N')
		Form::exitSystem(s);
	else
		return;
}

//9
void Form::addSellerBuyer(System& s)
{
	SellerBuyer sl;
	//getting user arrtibutes
	Form::askForUser(sl,s);
	while (!s.addUser(sl, SELLERBUYER))//loop to check succes of the task
	{
		cout << "\nUser already exist in the system, press Enter to try different user:" << endl;
		Form::askForUser(sl,s);
	}
}

//10
void Form::showAllSellerBuyers(System& s)
{
	SellerBuyer* b_temp;
	bool found = false;
	//check if there are buyers in the system
	cout << "\nSystem Users (buyers and sellers):";
	for (int i = 0; i < s.getNumOfUsers();i++)
		if (Validate::isBuyer(*s.getUsers()[i]) && Validate::isSeller(*s.getUsers()[i]))
		{
			found = true;
			b_temp = dynamic_cast<SellerBuyer*>(s.getUsers()[i]);
			b_temp->show();
		}

	if (!found)
	{
		cout << "\nNot Users that are buyers and sellers in the system";
		chooseMenu(s);
		return;
	}
	chooseMenu(s);
}

//10
void Form::showCertainUsersByType(System& s)
{
	int type;
	cout << "\nPlease enter the type of user to show: Buyers-0, Sellers-1, SellerBuyers-2: ";
	cin >> type;
	if (type > 2 || type < 0)
	{
		cout << "\nIllegal Choice!";
		chooseMenu(s);
		return;
	}

	switch (type)
	{
	case BUYER:
		Form::showAllBuyers(s);
		break;
	case SELLER:
		Form::showAllSellers(s);
		break;
	case SELLERBUYER:
		Form::showAllSellerBuyers(s);
		break;
	default:
		break;
	}
}

//11
void Form::compareTwoBuyers(System& s)
{
	string b1, b2;
	char d = getchar();
	int i, j, t;
	//check if there are Users in system
	if (s.getNumOfUsers() == 0)
	{
		cout << "\nNo Users in the system";
		chooseMenu(s);
		return;
	}
	//getting two buyers to comare
	cout << "\nPlease first buyer's name to compare: ";
	getline(cin, b1);
	i = s.getUserIndex(b1);
	cout << "\nPlease second buyer's name to compare: ";
	getline(cin, b2);
	j = s.getUserIndex(b2);
	//checking their validation
	if (i == -1 || j == -1 || i == j || !Validate::isBuyer(*s.getUsers()[i]) || !Validate::isBuyer(*s.getUsers()[j]))
	{
		cout << "\nInvalid input!";
		chooseMenu(s);
		return;
	}
	//calling system function for task 
	t = s.hasMoreExpensive(i, j);
	if (t == -2)
		cout << "\nBoth buyers has the same payment in cart";
	else if (t == -1)
		cout << "\nInvalid input!";
	else
		cout <<"\n"<< s.getUsers()[t]->getName() << " has bigger payment to his cart.";
	chooseMenu(s);
}

void Form::exitSystem(System& s)
{
	s.writeToFile();
	exit(0);
}