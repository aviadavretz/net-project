/*
 * ServerTerminalPrinter.cpp
 *
 *  Created on: Feb 17, 2017
 *      Author: user
 */


#include "ServerTerminalPrinter.h"

void ServerTerminalPrinter::printWelcomeMessage()
{
	cout << "Welcome to Naveh & Aviad's net project !" << endl;
	cout << "Server will start now..." << endl;
}

void ServerTerminalPrinter::printMenu()
{
	cout << "-------------------Menu--------------------" <<endl;
	cout << " 1. To list users: " << PRINT_ALL_USERS << endl;
	cout << " 2. To list connected users: " << PRINT_CONNECTED_USERS <<endl;
	cout << " 3. To list sessions: " << PRINT_SESSIONS <<endl;
	cout << " 4. To list Rooms: " << PRINT_ROOMS <<endl;
	cout << " 5. To list Users in Room: " << PRINT_ROOM_USERS << " <roomName>" <<endl;
	cout << " 6. To exit type: " << SHUTDOWN_SERVER <<endl;
	cout << "----------------------------------------------" <<endl;
}

void ServerTerminalPrinter::printUnknownCommand()
{
	cout << "The command you entered does not exist" << endl;
}

void ServerTerminalPrinter::printExitMessage()
{
	cout << "Goodbye !" << endl;
}

void ServerTerminalPrinter::print(vector<User*> users)
{

}

void ServerTerminalPrinter::print(vector<Session*> sessions)
{

}

void ServerTerminalPrinter::print(vector<ChatRoom*> rooms)
{

}

void ServerTerminalPrinter::printUsersName(vector<string> names)
{
	cout << "Registered users name:" << endl;

	for (vector<string>::iterator iterator = names.begin(); iterator != names.end(); iterator++)
	{
		cout << *iterator << endl;
	}
}


