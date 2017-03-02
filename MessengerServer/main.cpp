#include <iostream>
#include "ServerTerminalPrinter.h"
#include "UserInputCommands.h"
#include "ServerController.h"
#include "TCPSocket.h"
#include "CommandUtils.h"

using namespace std;
using namespace npl;

int main()
{
	ServerTerminalPrinter printer;
	printer.printWelcomeMessage();

	ServerController controller;
	controller.startServer();

	// TODO: CommandUtils... move it to a shared folder?
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
			printer.printUsersName(controller.getAllRegisteredUsersName());
		}
		else if (userCommand.compare(PRINT_CONNECTED_USERS) == 0)
		{
			printer.printConnectedUsersName(controller.getAllConnectedUsersName());
		}
		else if (userCommand.compare(PRINT_SESSIONS) == 0)
		{
			printer.print(controller.getAllSessions());
		}
		else if (userCommand.compare(PRINT_ROOMS) == 0)
		{
			printer.print(controller.getAllChatRooms());
		}
		else if (commandUtils.doesCommandHavePrefix(userCommand, PRINT_ROOM_USERS))
		{
			// TODO: UserInputCommands... move it to a shared folder?
			int PRINT_ROOM_USERS_ARGS_NUM = 1;

			// Get the args
			vector<string> args = commandUtils.getCommandArgs(userCommand, PRINT_ROOM_USERS);

			// Make sure we received the correct number of args
			if (args.size() != PRINT_ROOM_USERS_ARGS_NUM)
			{
				printer.printInvalidArgsNum();
				continue;
			}

			string roomName = args[0];

			ChatRoom* room = controller.getChatRoomByName(roomName);
			printer.printRoomUsers(room, roomName);
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

