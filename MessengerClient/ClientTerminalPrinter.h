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

using namespace std;

class ClientTerminalPrinter {
public:
	void printWelcomeMessage();
	void printMenu();
	void printUnknownCommand();
	void printExitMessage();
	void printInvalidArgsNum();

	void print(string str);
};

#endif /* CLIENTTERMINALPRINTER_H_ */
