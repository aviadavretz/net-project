/*
 * LoginManager.h
 *
 *  Created on: Feb 17, 2017
 *      Author: user
 */

#ifndef USERCREDENTIALSMANAGER_H_
#define USERCREDENTIALSMANAGER_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

#define USERS_FILE_NAME "users.txt"
#define PASSWORD_DELIMITER "@@@@@"

class UserCredentialsManager
{
private:
	bool doesFileLineMatchUserCredentials(string fileLine, string username, string password);
	bool writeUserCredentialsToFile(string username, string password);

public:
	bool signUp(string username, string password);
	bool validateUserCredentials(string username, string password);
	vector<string> getAllRegisteredUsersName();
	bool doesUsernameExist(string username);
};

#endif /* USERCREDENTIALSMANAGER_H_ */
