#include <iostream>
#include "ClientController.h"
#include "ClientTerminalPrinter.h"
#include "UserInputCommands.h"
#include "TCPSocket.h"
#include <vector>

using namespace std;
using namespace npl;

bool startsWith(string str, string prefix)
{
	int firstSpaceIndex = str.find_first_of(' ', 0);

	return str.substr(0, firstSpaceIndex).compare(prefix) == 0;
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
	TCPSocket* socket = NULL;

	while (shouldContinue)
	{
		printer.printMenu();

		string userCommand;
		std::getline(std::cin, userCommand);

		if (startsWith(userCommand, CONNECT))
		{
			vector<string> args = getCommandArgs(userCommand, CONNECT);

			if (args.size() != CONNECT_ARGS_NUM)
			{
				printer.printInvalidArgsNum();
				continue;
			}

			string address = args[0];

			printer.print(address);

			// TODO: Make sure we're not connected already
			socket = new TCPSocket(address, 3346);
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
		else if (startsWith(userCommand, LOGIN))
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
		else if (startsWith(userCommand, REGISTER))
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
		else if (userCommand.compare(OPEN_ROOM) == 0)
		{

		}
		else if (userCommand.compare(SEND_MESSAGE) == 0)
		{

		}
		else if (userCommand.compare(PRINT_STATUS) == 0)
		{
			if (socket == NULL)
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
			// TODO: Need to notify the server!
			socket->close();
			socket = NULL;

			printer.print("Disconnected from server.");
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
