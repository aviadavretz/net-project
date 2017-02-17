/*
 * LoginManager.cpp
 *
 *  Created on: Feb 17, 2017
 *      Author: user
 */

#include "LoginManager.h"

bool LoginManager::signUp(string username, string password)
{
	if (validateUserCredentials(username, password))
	{
		return false;
	}

	return writeUserCredentialsToFile(username, password);
}

bool LoginManager::validateUserCredentials(string username, string password)
{
	ifstream usersFile;
	usersFile.open(USERS_FILE_NAME, ios::in | ios::binary);

	if (usersFile.is_open())
	{
		string userLine;

		while (getline(usersFile, userLine))
		{
			if (doesFileLineMatchesUserCredentials(userLine, username, password))
			{
				usersFile.close();
				return true;
			}
		}

		usersFile.close();
	}

	return false;
}

bool LoginManager::doesFileLineMatchesUserCredentials(string fileLine, string username, string password)
{
	string passwordDelimiter = string(PASSWORD_DELIMITER);

	return (fileLine.length() == (username.length() + passwordDelimiter.length() + password.length())) &&
			(fileLine.compare(username + passwordDelimiter + password) == 0);
}

bool LoginManager::writeUserCredentialsToFile(string username, string password)
{
	ofstream usersFile;
	usersFile.open(USERS_FILE_NAME, ios::out | ios::app | ios::binary);

	if (usersFile.is_open())
	{
		usersFile << username + PASSWORD_DELIMITER + password << endl;
		usersFile.close();

		return true;
	}

	return false;
}

