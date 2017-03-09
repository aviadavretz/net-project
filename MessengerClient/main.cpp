#include "ClientController.h"
#include "ClientTerminalPrinter.h"
#include "UserInputCommands.h"
#include "TCPSocket.h"
#include <vector>
#include "CommandUtils.h"

using namespace std;
using namespace npl;

ClientController controller;
ClientTerminalPrinter printer;
CommandUtils commandUtils;

bool connected()
{
	// Make sure we're connected
	if (!controller.isConnected())
	{
		printer.print("You are not connected to a server.");
		return false;
	}

	return true;
}

bool notConnected()
{
	// Make sure we're not connected already
	if (controller.isConnected())
	{
		printer.print("You are already connected to a server.");
		return false;
	}

	return true;
}

int main()
{
	printer.printWelcomeMessage();
	bool shouldContinue = true;
	bool shouldPrintMenu = true;

	while (shouldContinue)
	{
		if (shouldPrintMenu)
		{
			printer.printMenu();
		}

		// Reset it
		shouldPrintMenu = true;

		// Get the whole command line from the user
		string userCommand;
		std::getline(std::cin, userCommand);

		// -------
		// CONNECT
		// -------
		if (commandUtils.doesCommandHavePrefix(userCommand, CONNECT_REQUEST))
		{
			if (notConnected())
			{
				// Get the args
				vector<string> args = commandUtils.getCommandArgs(userCommand, CONNECT_REQUEST);

				// Make sure we received the correct number of args
				if (args.size() != CONNECT_ARGS_NUM)
				{
					printer.printInvalidArgsNum();
					continue;
				}

				string address = args[0];

				controller.connect(address);
			}
		}
		// ---------------
		// PRINT_ALL_USERS
		// ---------------
		else if (userCommand.compare(PRINT_ALL_USERS) == 0)
		{
			if (connected())
			{
				controller.requestAllRegisterdUsersName();
			}
		}
		// ---------------------
		// PRINT_CONNECTED_USERS
		// ---------------------
		else if (userCommand.compare(PRINT_CONNECTED_USERS) == 0)
		{
			if (connected())
			{
				controller.requestAllConnectedUsersName();
			}
		}
		// -----------
		// PRINT_ROOMS
		// -----------
		else if (userCommand.compare(PRINT_ROOMS) == 0)
		{
			if (connected())
			{
				controller.requestAllRooms();
			}
		}
		// ---------------
		// PRINT_ROOM_USERS
		// ---------------
		else if (commandUtils.doesCommandHavePrefix(userCommand, PRINT_ROOM_USERS))
		{
			if (connected())
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

				controller.requestAllUsersInRoom(roomName);
			}
		}
		// -----
		// LOGIN
		// -----
		else if (commandUtils.doesCommandHavePrefix(userCommand, LOGIN_REQUEST))
		{
			if (connected())
			{
				// Get the args, and make sure the number of args is correct
				vector<string> args = commandUtils.getCommandArgs(userCommand, LOGIN_REQUEST);

				if (args.size() != LOGIN_ARGS_NUM)
				{
					printer.printInvalidArgsNum();
					continue;
				}

				string username = args[0];
				string password = args[1];

				controller.login(username, password);
			}
		}
		// --------
		// REGISTER
		// --------
		else if (commandUtils.doesCommandHavePrefix(userCommand, REGISTER_REQUEST))
		{
			if (connected())
			{
				// Get the args, and make sure the number of args is correct
				vector<string> args = commandUtils.getCommandArgs(userCommand, REGISTER_REQUEST);
				if (args.size() != REGISTER_ARGS_NUM)
				{
					printer.printInvalidArgsNum();
					continue;
				}

				string username = args[0];
				string password = args[1];

				controller.registerUser(username, password);
			}
		}
		// ------------
		// OPEN_SESSION
		// ------------
		else if (commandUtils.doesCommandHavePrefix(userCommand, OPEN_SESSION))
		{
			if (connected())
			{
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
		}
		// ---------
		// OPEN_ROOM
		// ---------
		else if (commandUtils.doesCommandHavePrefix(userCommand, OPEN_ROOM))
		{
			if (connected())
			{
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
		}
		// ---------
		// JOIN_ROOM
		// ---------
		else if (commandUtils.doesCommandHavePrefix(userCommand, JOIN_ROOM))
		{
			if (connected())
			{
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
		}
		// ------------
		// SEND_MESSAGE
		// ------------
		else if (commandUtils.doesCommandHavePrefix(userCommand, SEND_MESSAGE))
		{
			if (connected())
			{
				// Get the message (the single arg).
				string message = commandUtils.getCommandSingleArg(userCommand, SEND_MESSAGE);

				// Check if logged-in.
				if (controller.isLoggedIn())
				{
					// Make sure we are in a session/room, otherwise there's no recipient to the message.
					if (controller.isInSessionOrRoom())
					{
						// Get the username we saved when we logged-in successfully
						string sendingUsername = controller.getLoggedInUsername();

						// Send the message
						controller.sendMessage(sendingUsername, message);

						// A message was sent. Don't print menu now.
						shouldPrintMenu = false;
					}
					else
					{
						printer.print("No one to send messages to.");
					}
				}
				else
				{
					printer.print("You are not logged-in.");
				}
			}
		}
		// ------------
		// PRINT_STATUS
		// ------------
		else if (userCommand.compare(PRINT_STATUS) == 0)
		{
			if (connected())
			{
				// Go to server and check client status
				controller.requestStatus();
			}
		}
		// -------------
		// CLOSE_SESSION
		// EXIT_ROOM
		// -------------
		else if (userCommand.compare(CLOSE_SESSION_OR_EXIT_ROOM_REQUEST) == 0)
		{
			if (connected())
			{
				controller.closeSessionOrExitRoom();
			}
		}
		// ----------
		// CLOSE_ROOM
		// ----------
		else if (commandUtils.doesCommandHavePrefix(userCommand, CLOSE_ROOM_REQUEST))
		{
			if (connected())
			{
				// Get the args, and make sure the number of args is correct
				vector<string> args = commandUtils.getCommandArgs(userCommand, CLOSE_ROOM_REQUEST);
				if (args.size() != CLOSE_ROOM_ARGS_NUM)
				{
					printer.printInvalidArgsNum();
					continue;
				}

				string roomName = args[0];

				controller.closeRoom(roomName);
			}
		}
		// ----------
		// DISCONNECT
		// ----------
		else if (userCommand.compare(DISCONNECT_REQUEST) == 0)
		{
			if (connected())
			{
				controller.disconnect();
			}
		}
		// ----
		// EXIT
		// ----
		else if (userCommand.compare(EXIT_REQUEST) == 0)
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
