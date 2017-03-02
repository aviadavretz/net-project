#include "ClientController.h"
#include "ClientTerminalPrinter.h"
#include "UserInputCommands.h"
#include "TCPSocket.h"
#include <vector>
#include "CommandUtils.h"

using namespace std;
using namespace npl;

int main()
{
	ClientController controller;
	ClientTerminalPrinter printer;
	CommandUtils commandUtils;

	printer.printWelcomeMessage();
	bool shouldContinue = true;

	while (shouldContinue)
	{
		printer.printMenu();

		// Get the whole command line from the user
		string userCommand;
		std::getline(std::cin, userCommand);

		// -------
		// CONNECT
		// -------
		if (commandUtils.doesCommandHavePrefix(userCommand, CONNECT))
		{
			// Make sure we're not connected already
			if (controller.isConnected())
			{
				printer.print("You are already connected to a server.");
				continue;
			}

			// Get the args
			vector<string> args = commandUtils.getCommandArgs(userCommand, CONNECT);

			// Make sure we received the correct number of args
			if (args.size() != CONNECT_ARGS_NUM)
			{
				printer.printInvalidArgsNum();
				continue;
			}

			string address = args[0];

			controller.connect(address);
		}
		// ---------------
		// PRINT_ALL_USERS
		// ---------------
		else if (userCommand.compare(PRINT_ALL_USERS) == 0)
		{
			// Make sure we're connected
			if (!controller.isConnected())
			{
				printer.print("You are not connected to a server.");
				continue;
			}

			controller.requestAllRegisterdUsersName();
		}
		// ---------------------
		// PRINT_CONNECTED_USERS
		// ---------------------
		else if (userCommand.compare(PRINT_CONNECTED_USERS) == 0)
		{
			// Make sure we're connected
			if (!controller.isConnected())
			{
				printer.print("You are not connected to a server.");
				continue;
			}

			controller.requestAllConnectedUsersName();
		}
		// -----------
		// PRINT_ROOMS
		// -----------
		else if (userCommand.compare(PRINT_ROOMS) == 0)
		{
			// Make sure we're connected
			if (!controller.isConnected())
			{
				printer.print("You are not connected to a server.");
				continue;
			}

			controller.requestAllRooms();
		}
		// ---------------
		// PRINT_ROOM_USERS
		// ---------------
		else if (commandUtils.doesCommandHavePrefix(userCommand, PRINT_ROOM_USERS))
		{
			// Make sure we're connected
			if (!controller.isConnected())
			{
				printer.print("You are not connected to a server.");
				continue;
			}

			// Get the args
			vector<string> args = commandUtils.getCommandArgs(userCommand, PRINT_ROOM_USERS);

			// Make sure we received the correct number of args
			if (args.size() != PRINT_ROOM_USERS_ARGS_NUM)
			{
				printer.printInvalidArgsNum();
				continue;
			}

			string roomName = args[0];

			controller.requestAllUsersInRoom(roomName);
		}
		// -----
		// LOGIN
		// -----
		else if (commandUtils.doesCommandHavePrefix(userCommand, LOGIN))
		{
			// Make sure we are connected
			if (!controller.isConnected())
			{
				printer.print("You are not connected.");
				continue;
			}

			// Get the args, and make sure the number of args is correct
			vector<string> args = commandUtils.getCommandArgs(userCommand, LOGIN);

			if (args.size() != LOGIN_ARGS_NUM)
			{
				printer.printInvalidArgsNum();
				continue;
			}

			string username = args[0];
			string password = args[1];

			controller.login(username, password);
		}
		// --------
		// REGISTER
		// --------
		else if (commandUtils.doesCommandHavePrefix(userCommand, REGISTER))
		{
			// Make sure we are connected
			if (!controller.isConnected())
			{
				printer.print("You are not connected.");
				continue;
			}

			// Get the args, and make sure the number of args is correct
			vector<string> args = commandUtils.getCommandArgs(userCommand, REGISTER);
			if (args.size() != REGISTER_ARGS_NUM)
			{
				printer.printInvalidArgsNum();
				continue;
			}

			string username = args[0];
			string password = args[1];

			controller.registerUser(username, password);
		}
		// ------------
		// OPEN_SESSION
		// ------------
		else if (commandUtils.doesCommandHavePrefix(userCommand, OPEN_SESSION))
		{
			// Make sure we are connected
			if (!controller.isConnected())
			{
				printer.print("You are not connected.");
				continue;
			}

			// Get the args, and make sure the number of args is correct
			vector<string> args = commandUtils.getCommandArgs(userCommand, OPEN_SESSION);
			if (args.size() != OPEN_SESSION_ARGS_NUM)
			{
				printer.printInvalidArgsNum();
				continue;
			}

			string otherUserName = args[0];

			controller.openSession(otherUserName);
		}
		// ---------
		// OPEN_ROOM
		// ---------
		else if (commandUtils.doesCommandHavePrefix(userCommand, OPEN_ROOM))
		{
			// Make sure we are connected
			if (!controller.isConnected())
			{
				printer.print("You are not connected.");
				continue;
			}

			// Get the args, and make sure the number of args is correct
			vector<string> args = commandUtils.getCommandArgs(userCommand, OPEN_ROOM);
			if (args.size() != OPEN_ROOM_ARGS_NUM)
			{
				printer.printInvalidArgsNum();
				continue;
			}

			string roomName = args[0];

			controller.openRoom(roomName);
		}
		// ---------
		// JOIN_ROOM
		// ---------
		else if (commandUtils.doesCommandHavePrefix(userCommand, JOIN_ROOM))
		{
			// Make sure we are connected
			if (!controller.isConnected())
			{
				printer.print("You are not connected.");
				continue;
			}

			// Get the args, and make sure the number of args is correct
			vector<string> args = commandUtils.getCommandArgs(userCommand, JOIN_ROOM);
			if (args.size() != JOIN_ROOM_ARGS_NUM)
			{
				printer.printInvalidArgsNum();
				continue;
			}

			string roomName = args[0];

			controller.joinRoom(roomName);
		}
		// ------------
		// SEND_MESSAGE
		// ------------
		else if (commandUtils.doesCommandHavePrefix(userCommand, SEND_MESSAGE))
		{
			// Make sure we are connected
			if (!controller.isConnected())
			{
				printer.print("You are not connected.");
				continue;
			}

			// Get the args, and make sure the number of args is correct
			vector<string> args = commandUtils.getCommandArgs(userCommand, SEND_MESSAGE);
			if (args.size() != SEND_MESSAGE_ARGS_NUM)
			{
				printer.printInvalidArgsNum();
				continue;
			}

			string message = args[0];

			// TODO: Implement
		}
		// ------------
		// PRINT_STATUS
		// ------------
		else if (userCommand.compare(PRINT_STATUS) == 0)
		{
			// Make sure we are connected
			if (!controller.isConnected())
			{
				printer.print("You are not connected to a server");
				continue;
			}

			// Go to server and check client status
			controller.requestStatus();
		}
		// -------------
		// CLOSE_SESSION
		// EXIT_ROOM
		// -------------
		else if (userCommand.compare(CLOSE_SESSION_OR_EXIT_ROOM) == 0)
		{
			// Make sure we are connected
			if (!controller.isConnected())
			{
				printer.print("You are not connected to a server.");
				continue;
			}

			controller.closeSessionOrExitRoom();
		}
		// ----------
		// CLOSE_ROOM
		// ----------
		else if (commandUtils.doesCommandHavePrefix(userCommand, CLOSE_ROOM))
		{
			// Make sure we are connected
			if (!controller.isConnected())
			{
				printer.print("You are not connected.");
				continue;
			}

			// Get the args, and make sure the number of args is correct
			vector<string> args = commandUtils.getCommandArgs(userCommand, CLOSE_ROOM);
			if (args.size() != CLOSE_ROOM_ARGS_NUM)
			{
				printer.printInvalidArgsNum();
				continue;
			}

			string roomName = args[0];

			controller.closeRoom(roomName);
		}
		// ----------
		// DISCONNECT
		// ----------
		else if (userCommand.compare(DISCONNECT) == 0)
		{
			// Make sure we are connected
			if (!controller.isConnected())
			{
				printer.print("You are not connected to a server.");
				continue;
			}

			controller.disconnect();
		}
		// ----
		// EXIT
		// ----
		else if (userCommand.compare(EXIT) == 0)
		{
			// Check if we are connected
			if (controller.isConnected())
			{
				// Disconnect & close sockets
				controller.disconnect();
			}

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
