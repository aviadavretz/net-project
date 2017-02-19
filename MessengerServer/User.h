/*
 * User.h
 *
 *  Created on: Feb 7, 2017
 *      Author: user
 */

#ifndef USER_H_
#define USER_H_

#include <iostream>

using namespace std;

class User
{
	string username;

public:
	User(string username);
	string getUsername();
};


#endif /* USER_H_ */
