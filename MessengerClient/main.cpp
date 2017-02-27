#include <iostream>
#include "ClientController.h"
#include "ClientTerminalPrinter.h"
#include "UserInputCommands.h"
#include "TCPSocket.h"

using namespace std;
using namespace npl;

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
		cin >> userCommand;

		if (userCommand.compare(CONNECT) == 0)
		{
			socket = new TCPSocket("127.0.0.1", 3346);
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
			// FUCK THIS
			unsigned int LOGINz = 70;
			int EXPECTED_COMMAND_BYTES_SIZE = 4;

			int commandLength = htonl(LOGINz);
			socket->send((char*)&commandLength,4);

			string username;
			string password;
			cin >> username;
			cin >> password;

			string message = username.append(" ").append(password);

			cout << "Sending : " << message << endl;

			int messageLength = htonl(message.length());
			socket->send((char*)&messageLength, 4);
			socket->send(message);

			int command = 0;

			// Receive reply (the size should be as stated in the protocol)
			int bytesReceived = socket->recv((char*)&command, EXPECTED_COMMAND_BYTES_SIZE);

			cout << ntohl(command) << endl;
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
