#include <iostream>
#include "ServerTerminalPrinter.h"
#include "UserInputCommands.h"
#include "ServerController.h"
#include "TCPSocket.h"

using namespace std;
using namespace npl;

int main()
{
	ServerTerminalPrinter printer;
	printer.printWelcomeMessage();

	ServerController controller;
	controller.startServer();

	// Just for testing, should be removed.
	TCPSocket* socket;
	int kaki = true;

	bool shouldContinue = true;

	while (shouldContinue)
	{
		printer.printMenu();

		string userCommand;
		cin >> userCommand;

		if (userCommand.compare(PRINT_ALL_USERS) == 0)
		{
			printer.printUsersName(controller.getAllRegisteredUsersName());
		}
		else if (userCommand.compare(PRINT_CONNECTED_USERS) == 0)
		{
			printer.print(controller.getAllConnectedUsers());
		}
		else if (userCommand.compare(PRINT_SESSIONS) == 0)
		{
			printer.print(controller.getAllSessions());
		}
		else if (userCommand.compare(PRINT_ROOMS) == 0)
		{
			printer.print(controller.getAllChatRooms());
		}
		else if (userCommand.compare(PRINT_ROOM_USERS) == 0)
		{
			// TODO: Get args: room name
			printer.print(controller.getChatRoomByName("guh")->getParticipatingUsers());
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

