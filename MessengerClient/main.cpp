#include "ClientController.h"
#include "ClientTerminalPrinter.h"
#include "UserInputCommands.h"
#include "TCPSocket.h"
#include <vector>

using namespace std;
using namespace npl;

// TODO: Find a better way for this
bool connected = false;

bool commandStartsWith(string command, string prefix)
{
	int firstSpaceIndex = command.find_first_of(' ', 0);

	return command.substr(0, firstSpaceIndex).compare(prefix) == 0;
}

vector<string> getCommandArgs(string command, string prefix)
{
	vector<string> args;

	string argsString = command.substr(prefix.length()+1, command.length());

	for (int i=0; i<argsString.length(); i++)
	{
		int start = i;

		char currChar = argsString.at(i);

		while (currChar != ' ' && i+1 < argsString.length())
		{
			i++;
			currChar = argsString.at(i);
		}

		// If this is the last arg
		if (i+1 >= argsString.length())
		{
			i++;
		}

		// Add the current arg to the list
		args.push_back(argsString.substr(start, i));
	}

	return args;
}

int main()
{
	ClientController controller;
	ClientTerminalPrinter printer;

	printer.printWelcomeMessage();
	bool shouldContinue = true;

	// Just for testing, should be removed.
	TCPSocket* socket;

	while (shouldContinue)
	{
		printer.printMenu();

		string userCommand;
		std::getline(std::cin, userCommand);

		if (commandStartsWith(userCommand, CONNECT))
		{
			if (connected)
			{
				printer.print("You are already connected to " + socket->fromAddr());
				continue;
			}

			vector<string> args = getCommandArgs(userCommand, CONNECT);

			if (args.size() != CONNECT_ARGS_NUM)
			{
				printer.printInvalidArgsNum();
				continue;
			}

			string address = args[0];

			// TODO: Make sure we're not connected already
			socket = new TCPSocket(address, 3346);

			// TODO: TCPProtocol
			int EXPECTED_COMMAND_BYTES_SIZE = 4;
			int CONNECT_SUCCESS = 420;

			int command = 0;

			// Receive reply (the size should be as stated in the protocol)
			int bytesReceived = socket->recv((char*)&command, EXPECTED_COMMAND_BYTES_SIZE);

			int returnedCode = ntohl(command);

			if (returnedCode == CONNECT_SUCCESS)
			{
				cout << "Connected!" << endl;
				connected = true;
			}

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
		else if (commandStartsWith(userCommand, LOGIN))
		{
			vector<string> args = getCommandArgs(userCommand, LOGIN);

			if (args.size() != LOGIN_ARGS_NUM)
			{
				printer.printInvalidArgsNum();
				continue;
			}

			// TODO: Get this from TCPProtocol
unsigned int LOGINz = 70;
int EXPECTED_COMMAND_BYTES_SIZE = 4;
int LOGIN_SUCCEEDED = 202;
int ALREADY_LOGGED_IN = 200;
int BAD_USERNAME_PASSWORD = 201;

			int commandLength = htonl(LOGINz);
			socket->send((char*)&commandLength,4);

			string username = args[0];
			string password = args[1];

			string message = username.append(" ").append(password);

			cout << "Trying to login: " << message << endl;

			int messageLength = htonl(message.length());
			socket->send((char*)&messageLength, 4);
			socket->send(message);

			int command = 0;

			// Receive reply (the size should be as stated in the protocol)
			int bytesReceived = socket->recv((char*)&command, EXPECTED_COMMAND_BYTES_SIZE);

			int returnedCode = ntohl(command);

			if (returnedCode == LOGIN_SUCCEEDED)
			{
				cout << "Login successful!\nWelcome, " << username << endl;
			}
			else if (returnedCode == ALREADY_LOGGED_IN)
			{
				cout << "You are already logged in." << endl;
			}
			else if (returnedCode == BAD_USERNAME_PASSWORD)
			{
				cout << "User or password is incorrect." << endl;
			}
		}
		else if (commandStartsWith(userCommand, REGISTER))
		{
			vector<string> args = getCommandArgs(userCommand, REGISTER);

			if (args.size() != REGISTER_ARGS_NUM)
			{
				printer.printInvalidArgsNum();
				continue;
			}

			// TODO: Get this from TCPProtocol
unsigned int REGISTERz = 71;
int EXPECTED_COMMAND_BYTES_SIZE = 4;
int ALREADY_LOGGED_IN = 200;
int REGISTER_FAILURE = 203;
int REGISTER_SUCCEEDED = 204;
int USERNAME_EXISTS = 205;

			int commandLength = htonl(REGISTERz);
			socket->send((char*)&commandLength,4);

			string username = args[0];
			string password = args[1];

			string message = username.append(" ").append(password);

			cout << "Trying to register: " << message << endl;

			int messageLength = htonl(message.length());
			socket->send((char*)&messageLength, 4);
			socket->send(message);

			int command = 0;

			// Receive reply (the size should be as stated in the protocol)
			int bytesReceived = socket->recv((char*)&command, EXPECTED_COMMAND_BYTES_SIZE);

			int returnedCode = ntohl(command);

			if (returnedCode == REGISTER_SUCCEEDED)
			{
				cout << "Register successful as " << username << endl;
			}
			else if (returnedCode == USERNAME_EXISTS)
			{
				cout << "Username already exists." << endl;
			}
			else if (returnedCode == ALREADY_LOGGED_IN)
			{
				cout << "You are already logged in." << endl;
			}
			else if (returnedCode == REGISTER_FAILURE)
			{
				cout << "Registration failed, Please try again." << endl;
			}
		}
		else if (userCommand.compare(OPEN_SESSION) == 0)
		{

		}
		else if (commandStartsWith(userCommand, OPEN_ROOM))
		{
			if (!connected)
			{
				printer.print("You are not connected.");
				continue;
			}

			vector<string> args = getCommandArgs(userCommand, OPEN_ROOM);

			if (args.size() != OPEN_ROOM_ARGS_NUM)
			{
				printer.printInvalidArgsNum();
				continue;
			}

			string roomName = args[0];

			// TODO: Get this from TCPProtocol
int OPEN_ROOM_SUCCESS = 440;
int NOT_LOGGED_IN = 206;
int ROOM_NAME_EXISTS = 441;
unsigned int OPEN_CHAT_ROOMz = 11;
int EXPECTED_COMMAND_BYTES_SIZE = 4;

			int commandLength = htonl(OPEN_CHAT_ROOMz);
			socket->send((char*)&commandLength,4);

			int messageLength = htonl(roomName.length());
			socket->send((char*)&messageLength, 4);
			socket->send(roomName);

			int command = 0;

			// Receive reply (the size should be as stated in the protocol)
			int bytesReceived = socket->recv((char*)&command, EXPECTED_COMMAND_BYTES_SIZE);

			int returnedCode = ntohl(command);

			if (returnedCode == OPEN_ROOM_SUCCESS)
			{
				printer.print("Room '" + roomName + "' created.");
			}
			else if (returnedCode == NOT_LOGGED_IN)
			{
				printer.print("You are not logged in.");
			}
			else if (returnedCode == ROOM_NAME_EXISTS)
			{
				printer.print("A room with that name already exists.");
			}
		}
		else if (userCommand.compare(SEND_MESSAGE) == 0)
		{

		}
		else if (userCommand.compare(PRINT_STATUS) == 0)
		{
			if (!connected)
			{
				printer.print("You are not connected to server");
			}
			else
			{
				// Go to server and check client status
			}
		}
		else if (userCommand.compare(CLOSE_SESSION) == 0)
		{

		}
		else if (userCommand.compare(CLOSE_ROOM) == 0)
		{

		}
		else if (userCommand.compare(DISCONNECT) == 0)
		{
			if (!connected)
			{
				printer.print("You are not connected to a server.");
				continue;
			}

			// TODO: TCPProtocol
			int EXPECTED_COMMAND_BYTES_SIZE = 4;
			int DISCONNECT_SUCCESS = 421;
			int DISCONNECTz = 13;

			// Notify the server
			int commandLength = htonl(DISCONNECTz);
			socket->send((char*)&commandLength,4);

			int command = 0;

			// Receive reply (the size should be as stated in the protocol)
			int bytesReceived = socket->recv((char*)&command, EXPECTED_COMMAND_BYTES_SIZE);

			int returnedCode = ntohl(command);

			if (returnedCode == DISCONNECT_SUCCESS)
			{
				printer.print("Disconnected from server.");

				socket->close();
				socket = NULL;

				connected = false;
			}
		}
		else if (userCommand.compare(EXIT) == 0)
		{
			if (connected)
			{
				// TODO: disconnect & close sockets
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
