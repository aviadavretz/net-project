/*
 * User.cpp
 *
 *  Created on: Feb 17, 2017
 *      Author: user
 */

#include "User.h"

User::User(string username): username(username) {}

string User::getUsername()
{
	return username;
}
