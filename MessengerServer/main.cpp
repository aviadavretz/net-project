#include <iostream>
#include "ServerTerminalPrinter.h"
#include "UserInputCommands.h"
#include "ServerController.h"
#include "CommandUtils.h"

using namespace std;

int main()
{
	ServerTerminalPrinter printer;
	printer.printWelcomeMessage();

	ServerController controller;
	controller.startServer();

	CommandUtils commandUtils;

	bool shouldContinue = true;

	while (shouldContinue)
	{
		printer.printMenu();

		// Get the whole command line from the user
		string userCommand;
		std::getline(std::cin, userCommand);

		if (userCommand.compare(PRINT_ALL_USERS) == 0)
		{
			// Print all registered usernames
			printer.printUsersName(controller.getAllRegisteredUsersName());
		}
		else if (userCommand.compare(PRINT_CONNECTED_USERS) == 0)
		{
			// Print all connected usernames
			printer.printConnectedUsersName(controller.getAllConnectedUsersName());
		}
		else if (userCommand.compare(PRINT_SESSIONS) == 0)
		{
			// Print all sessions
			printer.print(controller.getAllSessions());
		}
		else if (userCommand.compare(PRINT_ROOMS) == 0)
		{
			// Print all room names
			printer.print(controller.getAllChatRooms());
		}
		else if (commandUtils.doesCommandHavePrefix(userCommand, PRINT_ROOM_USERS))
		{
			// Get the args
			vector<string> args = commandUtils.getCommandArgs(userCommand, PRINT_ROOM_USERS);

			// Make sure we received the correct number of args
			if (args.size() != PRINT_ROOM_USERS_ARGS_NUM)
			{
				printer.printInvalidArgsNum();
				continue;
			}

			string roomName = args[0];

			// Get the requested room
			ChatRoom* room = controller.getChatRoomByName(roomName);

			// Print the room users
			printer.printRoomUsers(room, roomName);
		}
		else if (userCommand.compare(SHUTDOWN_SERVER) == 0)
		{
			// Stop the server
			controller.stopServer();
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

