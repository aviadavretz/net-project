/*
 * LoginManager.h
 *
 *  Created on: Feb 17, 2017
 *      Author: user
 */

#ifndef LOGINMANAGER_H_
#define LOGINMANAGER_H_

#include "File.h"
#include <iostream>

using namespace std;

#define USERS_FILE_NAME "users.txt"
#define PASSWORD_DELIMITER "@"

class LoginManager
{
private:
	bool doesFileLineMatchesUserCredentials(string fileLine, string username, string password);
	bool writeUserCredentialsToFile(string username, string password);

public:
	bool signUp(string username, string password);
	bool validateUserCredentials(string username, string password);
};

#endif /* LOGINMANAGER_H_ */
