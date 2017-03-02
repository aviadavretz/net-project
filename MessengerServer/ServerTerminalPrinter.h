/*
 * ServerTerminalPrinter.h
 *
 *  Created on: Feb 17, 2017
 *      Author: user
 */

#ifndef SERVERTERMINALPRINTER_H_
#define SERVERTERMINALPRINTER_H_

#include "User.h"
#include "Session.h"
#include "ChatRoom.h"
#include "string"
#include "UserInputCommands.h"
#include <vector>

using namespace std;

class ServerTerminalPrinter
{
	public:
	void printWelcomeMessage();
	void printMenu();
	void printUnknownCommand();
	void printExitMessage();
	void printConnectedUsersName(vector<string> users);
	void print(vector<Session*> sessions);
	void print(vector<ChatRoom*> rooms);
	void printUsersName(vector<string> names);
	void printRoomUsers(ChatRoom* room, string requestedRoomName);
	void printNewPeerAccepted(string addr);
	void printLoginSuccessful(string username, string addr);

	void print(string str);
};


#endif /* SERVERTERMINALPRINTER_H_ */
