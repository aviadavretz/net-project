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
	cout << " 1. To connect to server: " << CONNECT << " <IP>" << endl;
	cout << " 2. To list all users: " << PRINT_ALL_USERS <<endl;
	cout << " 3. To list connected users: " << PRINT_CONNECTED_USERS << endl;
	cout << " 4. To list Rooms: " << PRINT_ROOMS << endl;
	cout << " 5. To list Users in Room: " << PRINT_ROOM_USERS << " <RoomName>" << endl;
	cout << " 6. To login: " << LOGIN << " <UserName> <Password>" << endl;
	cout << " 7. To register: " << REGISTER << " <UserName> <Password>" << endl;
	cout << " 8. To open a session: " << OPEN_SESSION << " <UserName>" << endl;
	cout << " 9. To open a room: " << OPEN_ROOM << " <RoomName>" << endl;
	cout << " 10. To send a message: " << SEND_MESSAGE << " <Message>" << endl;
	cout << " 11. To get your status: " << PRINT_STATUS << endl;
	cout << " 12. To close session: " << CLOSE_SESSION << endl;
	cout << " 13. To close a room: " << CLOSE_ROOM << " <RoomName>" << endl;
	cout << " 14. To disconnect from server: " << DISCONNECT << endl;
	cout << " 15. To exit: " << EXIT << endl;
	cout << "----------------------------------------------" << endl;
}

void ClientTerminalPrinter::printUnknownCommand()
{
	cout << "The command you entered does not exist" << endl;
}

void ClientTerminalPrinter::printExitMessage()
{
	cout << "Goodbye !" << endl;
}
