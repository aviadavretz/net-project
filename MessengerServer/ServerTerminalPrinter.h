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
	void print(vector<User*> users);
	void print(vector<Session*> sessions);
	void print(vector<ChatRoom*> rooms);
};


#endif /* SERVERTERMINALPRINTER_H_ */
