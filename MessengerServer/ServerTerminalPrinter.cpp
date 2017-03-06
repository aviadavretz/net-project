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
	cout << "------------------- Menu - Server --------------------" <<endl;
	cout << " 1. To list users: " << PRINT_ALL_USERS << endl;
	cout << " 2. To list connected users: " << PRINT_CONNECTED_USERS <<endl;
	cout << " 3. To list sessions: " << PRINT_SESSIONS <<endl;
	cout << " 4. To list Rooms: " << PRINT_ROOMS <<endl;
	cout << " 5. To list Users in Room: " << PRINT_ROOM_USERS << " <roomName>" <<endl;
	cout << " 6. To exit type: " << SHUTDOWN_SERVER <<endl;
	cout << "----------------------------------------------" <<endl;
}

void ServerTerminalPrinter::print(string str)
{
	cout << str << endl;
}

void ServerTerminalPrinter::printListenPort(string addr, int port)
{
	cout << addr + " is listening on port " << port << endl;
}

void ServerTerminalPrinter::printNewPeerAccepted(string addr)
{
	cout << "New peer accepted: " << addr << endl;
}

void ServerTerminalPrinter::printLoginSuccessful(string username, string addr)
{
	cout << username << " (" << addr << ") has logged in." << endl;
}

void ServerTerminalPrinter::printInvalidArgsNum()
{
	cout << "Invalid number of arguments." << endl;
}

void ServerTerminalPrinter::printUnknownCommand()
{
	cout << "The command you entered does not exist" << endl;
}

void ServerTerminalPrinter::printExitMessage()
{
	cout << "Goodbye !" << endl;
}

void ServerTerminalPrinter::printConnectedUsersName(vector<string> users)
{
	if (users.empty())
	{
		cout << "There are no logged in users." << endl;
	}
	else
	{
		cout << "Online users:" << endl;

		for (vector<string>::iterator iterator = users.begin(); iterator != users.end(); iterator++)
		{
			cout << (*iterator) << endl;
		}
	}
}

void ServerTerminalPrinter::printRoomUsers(ChatRoom* room, string requestedRoomName)
{
	if (room == NULL)
	{
		cout << "The room '" << requestedRoomName << "' does not exist." << endl;;
	}
	else
	{
		vector<User*> roomUsers = room->getParticipatingUsers();

		if (roomUsers.empty())
		{
			cout << "There are no users in the room '" << requestedRoomName << "'." << endl;;
		}
		else
		{
			cout << "Room users at '" << requestedRoomName << "':" << endl;

			for (vector<User*>::iterator iterator = roomUsers.begin(); iterator != roomUsers.end(); iterator++)
			{
				cout << (*iterator)->getUsername() << endl;
			}
		}
	}
}

void ServerTerminalPrinter::print(vector<Session*> sessions)
{
	if (sessions.empty())
	{
		cout << "There are no open sessions." << endl;
	}
	else
	{
		cout << "Sessions:" << endl;

		for (vector<Session*>::iterator iterator = sessions.begin(); iterator != sessions.end(); iterator++)
		{
			cout << (*iterator)->getFirstUser()->getUsername()
				 << " and "
				 << (*iterator)->getSecondUser()->getUsername() << endl;
		}
	}
}

void ServerTerminalPrinter::print(vector<ChatRoom*> rooms)
{
	if (rooms.empty())
	{
		cout << "There are no open chat rooms." << endl;
	}
	else
	{
		cout << "Chat rooms:" << endl;

		for (vector<ChatRoom*>::iterator iterator = rooms.begin(); iterator != rooms.end(); iterator++)
		{
			cout << (*iterator)->getName() << endl;
		}
	}
}

void ServerTerminalPrinter::printUsersName(vector<string> names)
{
	cout << "Registered users name:" << endl;

	for (vector<string>::iterator iterator = names.begin(); iterator != names.end(); iterator++)
	{
		cout << *iterator << endl;
	}
}


