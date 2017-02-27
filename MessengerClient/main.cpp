#include <iostream>
#include "ClientController.h"
#include "ClientTerminalPrinter.h"
#include "UserInputCommands.h"

int main()
{
	ClientController controller;
	ClientTerminalPrinter printer;

	printer.printWelcomeMessage();
	bool shouldContinue = true;

	while (shouldContinue)
	{
		printer.printMenu();

		string userCommand;
		cin >> userCommand;

		if (userCommand.compare(CONNECT) == 0)
		{

		}
		else if (userCommand.compare(PRINT_ALL_USERS) == 0)
		{

		}
		else if (userCommand.compare(PRINT_CONNECTED_USERS) == 0)
		{

		}
		else if (userCommand.compare(PRINT_ROOMS) == 0)
		{

		}
		else if (userCommand.compare(LOGIN) == 0)
		{

		}
		else if (userCommand.compare(REGISTER) == 0)
		{

		}
		else if (userCommand.compare(OPEN_SESSION) == 0)
		{

		}
		else if (userCommand.compare(OPEN_ROOM) == 0)
		{

		}
		else if (userCommand.compare(SEND_MESSAGE) == 0)
		{

		}
		else if (userCommand.compare(PRINT_STATUS) == 0)
		{

		}
		else if (userCommand.compare(CLOSE_SESSION) == 0)
		{

		}
		else if (userCommand.compare(CLOSE_ROOM) == 0)
		{

		}
		else if (userCommand.compare(DISCONNECT) == 0)
		{

		}
		else if (userCommand.compare(EXIT) == 0)
		{
			printer.printExitMessage();
			shouldContinue = false;
		}
		else
		{
			printer.printUnknownCommand();
		}
	}

	return 0;
}
