#ifndef _USER_H
#define _USER_H

#include "address.h"

class User {
public:
	//c'tors and d'tor
	User() = default;
	User(const string& name, const string& password, const Address& address);
	User(const User& other);
	
	//getters
	const string& getName() const;
	const string& getPassword() const;
	const Address& getAddress() const;

	//setters
	bool setName(const string& name);
	bool setAddress(const Address& address);
	bool setPassword(const string& password);
	virtual bool operator=(const User& other);
	
	//show  
	virtual void show() const;
	virtual User* clone() const = 0;

protected:
	string name;
	string password;
	Address address;
};

#endif