/*
 * LoginManager.cpp
 *
 *  Created on: Feb 17, 2017
 *      Author: user
 */

#include "LoginManager.h"

bool LoginManager::signIn(string username, string password)
{
	if (doesUserExist(username))
	{
		return false;
	}

	return true;
}


bool LoginManager::doesUserExist(string username)
{
	return tryFindingUserPassword(username) != NULL;
}

bool LoginManager::signIn(string username, string password)
{
	return tryFindingUserPassword(username).compare(password) == 0;
}

string LoginManager::tryFindingUserPassword(string username)
{
	return "zibi";
}
