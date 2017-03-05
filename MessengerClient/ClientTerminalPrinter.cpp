/*
 * ClientTerminalPrinter.cpp
 *
 *  Created on: Feb 27, 2017
 *      Author: user
 */

#include "ClientTerminalPrinter.h"
#include <iostream>
#include <sstream>

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

void ClientTerminalPrinter::print(string str)
{
	cout << str << endl;
}

void ClientTerminalPrinter::printUnknownReplyCode(int replyCode)
{
	std::ostringstream strStream;
	strStream << "Unknown Reply-code: " << replyCode;
	cout << strStream.str() << endl;
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

void ClientTerminalPrinter::printUsersInRoom(vector<string> roomUsers)
{
	print("Users connected to room:");
	printStringList(roomUsers);
}
