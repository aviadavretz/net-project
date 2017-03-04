/*
 * ClientTerminalPrinter.h
 *
 *  Created on: Feb 27, 2017
 *      Author: user
 */

#ifndef CLIENTTERMINALPRINTER_H_
#define CLIENTTERMINALPRINTER_H_

#include "string"
#include "UserInputCommands.h"
#include "TCPMessengerProtocol.h"
#include <vector>

using namespace std;

class ClientTerminalPrinter {
	void printStringList(vector<string> messages);
public:
	void printWelcomeMessage();
	void printMenu();
	void printUnknownCommand();
	void printExitMessage();
	void printInvalidArgsNum();
	void printServerReplyMessage(int replyCode, string relevantData);
	void printServerReplyMessage(int replyCode);
	void print(string str);
	void printRegisteredUsers(vector<string> registeredUsers);
	void printConnectedUsers(vector<string> connectedUsers);
	void printRooms(vector<string> rooms);
	void printUsersInRoom(vector<string> roomUsers);
};

#endif /* CLIENTTERMINALPRINTER_H_ */
