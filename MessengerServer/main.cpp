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
			int commandLength = htonl(LOGIN);
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
		}
		else if (userCommand.compare(PRINT_CONNECTED_USERS) == 0)
		{
			int commandLength = htonl(REGISTER);
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
		}
		else if (userCommand.compare(PRINT_SESSIONS) == 0)
		{
			if (kaki)
				socket = new TCPSocket("127.0.0.1", MSNGR_PORT);
			kaki = false;
		}
		else if (userCommand.compare(PRINT_ROOMS) == 0)
		{
			kaki = true;
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

