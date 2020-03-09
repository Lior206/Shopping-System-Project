#ifndef _FORM_H
#define _FORM_H
#include "system.h"
#include "user.h"
#include "address.h"
#define MAX_LEN 80

//class for whose role is to communicate with the user
class Form
{
public:
	//all static function that change the system
	static void askForUser(User& u, System& s);
	static void addSeller(System& s);
	static void addSellerBuyer(System& s);
	static void addBuyer(System& s);
	static void printInteractiveMenu();
	static void chosenMethod(System& s, int choice);
	static void showAllBuyers(System& s);
	static void showAllSellers(System& s);
	static void showAllSellerBuyers(System& s);
	static void addProductToSeller(System& s);
	static void addProductToBuyerCart(System& s);
	static void showCertainProducts(System& s);
	static void createOrderForBuyer(System& s);
	static void closeOrderForBuyer(System& s);
	static void addFeedbackToSeller(System& s);
	static void showCertainUsersByType(System& s);
	static void compareTwoBuyers(System& s);
	static void chooseMenu(System& s);
	static void exitSystem(System& s);
};
#endif