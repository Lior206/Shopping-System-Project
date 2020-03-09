#include "main.h"
/*
Lior Chen 316522408
Yuval Raz 312270887
קבוצה ב-ימי שלישי
*/
int main()
{
	int choice = 0;
	System s;

	while (choice != 12)
	{
		system("CLS"); //clearing the screen 
		Form::printInteractiveMenu(); //print menu
		cout << "Choose an action:" << endl;
		cin >> choice;
		if (choice >= 1 && choice <= 12)
			Form::chosenMethod(s, choice);
		else
			cout << "Invalid choice, choose again." << endl;
	}
	return 0;
}