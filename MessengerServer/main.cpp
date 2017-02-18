#include <iostream>
#include "ServerTerminalPrinter.h"
#include "UserInputCommands.h"
#include "ServerController.h"

using namespace std;
using namespace npl;

int main()
{
	ServerTerminalPrinter printer;
	printer.printWelcomeMessage();

	ServerController controller;
	controller.startServer();

	bool shouldContinue = true;

	while (shouldContinue)
	{
		printer.printMenu();

		string userCommand;
		cin >> userCommand;

		if (userCommand.compare(PRINT_ALL_USERS) == 0)
		{

		}
		else if (userCommand.compare(PRINT_CONNECTED_USERS) == 0)
		{

		}
		else if (userCommand.compare(PRINT_SESSIONS) == 0)
		{

		}
		else if (userCommand.compare(PRINT_ROOMS) == 0)
		{

		}
		else if (userCommand.compare(PRINT_ROOM_USERS) == 0)
		{

		}
		else if (userCommand.compare(SHUTDOWN_SERVER) == 0)
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

