/*
 * ClientTerminalPrinter.cpp
 *
 *  Created on: Feb 27, 2017
 *      Author: user
 */

#include "ClientTerminalPrinter.h"
#include <iostream>

void ClientTerminalPrinter::printWelcomeMessage()
{
	cout << "Welcome to Naveh & Aviad's net project !" << endl;
}

void ClientTerminalPrinter::printMenu()
{
	cout << "------------------- Menu - Client --------------------" << endl;
	cout << " 1.  To connect to server: " << CONNECT_REQUEST << " <IP>" << endl;
	cout << " 2.  To list all users: " << PRINT_ALL_USERS <<endl;
	cout << " 3.  To list connected users: " << PRINT_CONNECTED_USERS << endl;
	cout << " 4.  To list Rooms: " << PRINT_ROOMS << endl;
	cout << " 5.  To list Users in Room: " << PRINT_ROOM_USERS << " <RoomName>" << endl;
	cout << " 6.  To login: " << LOGIN_REQUEST << " <UserName> <Password>" << endl;
	cout << " 7.  To register: " << REGISTER_REQUEST << " <UserName> <Password>" << endl;
	cout << " 8.  To open a session: " << OPEN_SESSION << " <UserName>" << endl;
	cout << " 9.  To open a room: " << OPEN_ROOM << " <RoomName>" << endl;
	cout << " 10. To join a room: " << JOIN_ROOM << " <RoomName>" << endl;
	cout << " 11. To send a message: " << SEND_MESSAGE << " <Message>" << endl;
	cout << " 12. To get your status: " << PRINT_STATUS << endl;
	cout << " 13. To close session or exit room: " << CLOSE_SESSION_OR_EXIT_ROOM_REQUEST << endl;
	cout << " 14. To close a room: " << CLOSE_ROOM_REQUEST << " <RoomName>" << endl;
	cout << " 15. To disconnect from server: " << DISCONNECT_REQUEST << endl;
	cout << " 16. To exit: " << EXIT_REQUEST << endl;
	cout << "----------------------------------------------" << endl;
}

// TODO: Delete this when finished with the project
void ClientTerminalPrinter::print(string str)
{
	cout << str << endl;
}

void ClientTerminalPrinter::printInvalidArgsNum()
{
	cout << "Invalid number of arguments." << endl;
}

void ClientTerminalPrinter::printUnknownCommand()
{
	cout << "The command you entered does not exist" << endl;
}

void ClientTerminalPrinter::printExitMessage()
{
	cout << "Goodbye !" << endl;
}

void ClientTerminalPrinter::printServerReplyMessage(int replyCode)
{
	printServerReplyMessage(replyCode, "");
}

void ClientTerminalPrinter::printServerReplyMessage(int replyCode, string relevantData)
{
	switch (replyCode)
	{
		case (CONNECT_SUCCESS):
		{
			print("Connected to " + relevantData);
			break;
		}
		case (BAD_USERNAME_PASSWORD):
		{
			print("Username or password is incorrect.");
			break;
		}
		case (CLIENT_ALREADY_LOGGED_IN):
		{
			print("You are already logged in.");
			break;
		}
		case (USER_ALREADY_LOGGED_IN):
		{
			print(relevantData + " is already logged in.");
			break;
		}
		case (LOGIN_SUCCEEDED):
		{
			print("Login successful!\nWelcome, " + relevantData);
			break;
		}
		case (REGISTER_FAILURE):
		{
			print("Registration failed, Please try again.");
			break;
		}
		case (USERNAME_EXISTS):
		{
			print("Username '" + relevantData + "' already exists.");
			break;
		}
		case (REGISTER_SUCCEEDED):
		{
			print("Register successful as " + relevantData);
			break;
		}
		case (NOT_LOGGED_IN):
		{
			print("You are not logged in.");
			break;
		}
		case (ALREADY_BUSY):
		{
			print("You are already participating in a session or room.");
			break;
		}
		case (SESSION_WITH_SELF):
		{
			print("You can't create a session with yourself, " + relevantData + "!");
			break;
		}
		case (USER_NOT_FOUND):
		{
			print(relevantData + " is either logged off or does not exist.");
			break;
		}
		case (OTHER_USER_BUSY):
		{
			print(relevantData + " is busy.");
			break;
		}
		case (ROOM_NAME_EXISTS):
		{
			print("A room named " + relevantData + " already exists.");
			break;
		}
		case (ROOM_DOES_NOT_EXIST):
		{
			print("There is no room named '" + relevantData + "'.");
			break;
		}
		case (NOT_IN_SESSION_OR_ROOM):
		{
			print("You are not in a session or room.");
			break;
		}
		case (NOT_ROOM_OWNER):
		{
			print("You are not the room owner.");
			break;
		}
		case (STATUS_FREE):
		{
			print("You are logged in, but not in a room/session.");
			break;
		}
		case (STATUS_IN_A_ROOM):
		{
			print("You are in a room.");
			break;
		}
		case (STATUS_IN_A_SESSION):
		{
			print("You are in a session.");
			break;
		}
		default:
		{
			print("Unknown reply-code.");
		}
	}
}

void ClientTerminalPrinter::printStringList(vector<string> messages)
{
	for (vector<string>::iterator iterator = messages.begin(); iterator != messages.end(); iterator++)
	{
		print(*iterator);
	}

}

void ClientTerminalPrinter::printRegisteredUsers(vector<string> registeredUsers)
{
	print("Registered Users:");
	printStringList(registeredUsers);
}

void ClientTerminalPrinter::printConnectedUsers(vector<string> connectedUsers)
{
	print("Connected Users:");
	printStringList(connectedUsers);
}

void ClientTerminalPrinter::printRooms(vector<string> rooms)
{
	print("Open chat-rooms:");
	printStringList(rooms);
}

void ClientTerminalPrinter::printUsersInRoom(vector<string> roomUsers, string roomName)
{
	print("Users in connected to '" + roomName + "' :");
	printStringList(roomUsers);
}
