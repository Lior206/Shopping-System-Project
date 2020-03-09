#ifndef _FEEDBACK_H
#define _FEEDBACK_H

#include <iostream>
using namespace std;
#include "buyer.h"
#include "date.h"

class Feedback
{
public:
	//c'tors and d'tor
	Feedback() = default;
	Feedback(const Buyer& buyer, const Date& date, const string& review);
	Feedback(const Feedback& feedback);
	

	//getters and setters
	const Buyer& getBuyer() const;
	const Date& getDate() const;
	const string& getReview() const;

	bool operator=(const Feedback& feedback);
	bool setBuyer(const Buyer& buyer);
	bool setDate(const Date& date);
	bool setReview(const string& review);

	//show
	friend ostream& operator<<(ostream& os, const Feedback& f);

private:
	Buyer buyer;
	Date date;
	string review;
};

#endif