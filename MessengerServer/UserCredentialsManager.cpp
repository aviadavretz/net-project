/*
 * LoginManager.cpp
 *
 *  Created on: Feb 17, 2017
 *      Author: user
 */

#include "UserCredentialsManager.h"

bool UserCredentialsManager::signUp(string username, string password)
{
	// Sign up
	return writeUserCredentialsToFile(username, password);
}

bool UserCredentialsManager::validateUserCredentials(string username, string password)
{
	// Open the users file with read permission
	ifstream usersFile;
	usersFile.open(USERS_FILE_NAME, ios::in | ios::binary);

	if (usersFile.is_open())
	{
		string userLine;

		// Go over all the lines in the file
		while (getline(usersFile, userLine))
		{
			// If the userLine describes the username & password
			if (doesFileLineMatchUserCredentials(userLine, username, password))
			{
				// Close the file
				usersFile.close();
				return true;
			}
		}

		// Close the file anyway
		usersFile.close();
	}

	return false;
}

bool UserCredentialsManager::doesFileLineMatchUserCredentials(string fileLine, string username, string password)
{
	string passwordDelimiter = string(PASSWORD_DELIMITER);

	// Make sure the lines are the same length before comparing them.
	return (fileLine.length() == (username.length() + passwordDelimiter.length() + password.length())) &&
			// Compare the lines
			(fileLine.compare(username + passwordDelimiter + password) == 0);
}

bool UserCredentialsManager::writeUserCredentialsToFile(string username, string password)
{
	// Open the file with write permission.
	ofstream usersFile;
	usersFile.open(USERS_FILE_NAME, ios::out | ios::app | ios::binary);

	if (usersFile.is_open())
	{
		// Write the username and password into the file
		usersFile << username + PASSWORD_DELIMITER + password << endl;
		usersFile.close();

		return true;
	}

	return false;
}

vector<string> UserCredentialsManager::getAllRegisteredUsersName()
{
	vector<string> usernames;

	// Open the file with read permission
	ifstream usersFile;
	usersFile.open(USERS_FILE_NAME, ios::in | ios::binary);

	if (usersFile.is_open())
	{
		string userLine;

		// Go over all the lines in the file
		while (getline(usersFile, userLine))
		{
			// Find the index of the delimiter
			string::size_type delimiterIndex = userLine.find(PASSWORD_DELIMITER, 0);

			// If it exists
			if (delimiterIndex != string::npos)
			{
				// Cut only the username, and add it
				usernames.push_back(userLine.substr(0, delimiterIndex));
			}
		}

		// Close the file
		usersFile.close();
	}

	return usernames;
}

bool UserCredentialsManager::doesUsernameExist(string username)
{
	// Fetch all registered usernames
	vector<string> usernames = getAllRegisteredUsersName();

	// Find the position of the requested username, and return whether it exists.
	return find(usernames.begin(), usernames.end(), username) != usernames.end();
}


