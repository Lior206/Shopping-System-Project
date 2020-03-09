#define _CRT_SECURE_NO_WARNINGS

#include "feedback.h"
#include "validate.h"
//c'tors
Feedback::Feedback(const Buyer& buyer, const Date& date, const string& review) :buyer(buyer), date(date)
{
	this->setReview(review);
}

Feedback::Feedback(const Feedback& feedback)
{
	*this = feedback;
}


//getters
const Buyer& Feedback::getBuyer() const
{
	return this->buyer;
}

const Date& Feedback::getDate() const
{
	return this->date;
}

const string& Feedback::getReview() const
{
	return this->review;
}

//setters
bool Feedback::setBuyer(const Buyer& buyer)
{
	return this->buyer = buyer;
}

bool Feedback::setDate(const Date& date)
{
	return this->date.setCopy(date);
}

bool Feedback::setReview(const string& review)
{
	if (Validate::review(review))
	{
		this->review = review;
		return true;
	}
	else
		return false;
}

bool Feedback::operator=(const Feedback& feedback)
{
	return this->setBuyer(feedback.getBuyer()) &&
		this->setDate(feedback.getDate()) &&
		this->setReview(feedback.getReview());
}

//show
ostream& operator<<(ostream& os, const Feedback& f)
{
	os << "\nFrom: " << f.buyer.getName();
	os << "\nAt: ";
	os << f.date;
	cout << "\nReview:" << f.review;
	return os;
}
