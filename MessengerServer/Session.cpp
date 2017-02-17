/*
 * Session.cpp
 *
 *  Created on: Feb 17, 2017
 *      Author: user
 */

#include "Session.h"

Session::Session(User* firsUser, User* secondUser)
{
	this->firstUser = firsUser;
	this->secondUser = secondUser;
}

User* Session::getFirstUser()
{
	return firstUser;
}

User* Session::getSecondUser()
{
	return secondUser;
}
