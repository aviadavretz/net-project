
/*
 * ClientController.cpp
 *
 *  Created on: Feb 27, 2017
 *      Author: user
 */

#include "ClientController.h"

ClientController::ClientController()
{
	connected = false;
}

bool ClientController::isConnected()
{
	return connected;
}

void ClientController::manageReply(int replyCode, string relevantData)
{
	// TODO: @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	// TODO: Get these from TCPProtocol
	const int CONNECT_SUCCESS = 420;

	const int LOGIN_SUCCEEDED = 202;
	const int CLIENT_ALREADY_LOGGED_IN = 200;
	const int USER_ALREADY_LOGGED_IN = 207;
	const int BAD_USERNAME_PASSWORD = 201;

	const int REGISTER_FAILURE = 203;
	const int REGISTER_SUCCEEDED = 204;
	const int USERNAME_EXISTS = 205;

	const int SESSION_ESTABLISHED = 6;
	const int NOT_LOGGED_IN = 206;
	const int ALREADY_BUSY = 462;
	const int USER_NOT_FOUND = 522;
	const int OTHER_USER_BUSY = 523;
	const int SESSION_WITH_SELF = 524;

	const int OPEN_ROOM_SUCCESS = 440;
	const int ROOM_NAME_EXISTS = 441;

	const int JOIN_ROOM_SUCCESS = 460;
	const int ROOM_DOES_NOT_EXIST = 461;

	const int EXIT_ROOM_SUCCESS = 480;
	const int NOT_IN_SESSION_OR_ROOM = 481;
	const int CLOSE_SESSION_SUCCESS = 490;

	const int CLOSE_ROOM_SUCCESS = 500;
	const int NOT_ROOM_OWNER = 501;

	const int STATUS_FREE = 540;
	const int STATUS_IN_A_ROOM = 541;
	const int STATUS_IN_A_SESSION = 542;

	const int DISCONNECT_SUCCESS = 421;

	const int GET_REGISTERED_USERS = 7;
	const int GET_CONNECTED_USERS = 8;
	const int GET_CHAT_ROOMS = 9;
	const int GET_USERS_IN_CHAT_ROOM = 10;

	switch (replyCode)
	{
		case (CONNECT_SUCCESS):
		{
			printer.print("Connected to " + relevantData);
			connected = true;
			break;
		}
		case (BAD_USERNAME_PASSWORD):
		{
			printer.print("Username or password is incorrect.");
			break;
		}
		case (CLIENT_ALREADY_LOGGED_IN):
		{
			printer.print("You are already logged in.");
			break;
		}
		case (USER_ALREADY_LOGGED_IN):
		{
			printer.print(relevantData + " is already logged in.");
			break;
		}
		case (LOGIN_SUCCEEDED):
		{
			printer.print("Login successful!\nWelcome, " + relevantData);
			break;
		}
		case (REGISTER_FAILURE):
		{
			printer.print("Registration failed, Please try again.");
			break;
		}
		case (USERNAME_EXISTS):
		{
			printer.print("Username '" + relevantData + "' already exists.");
			break;
		}
		case (REGISTER_SUCCEEDED):
		{
			printer.print("Register successful as " + relevantData);
			break;
		}
		case (SESSION_ESTABLISHED):
		{
			// TODO: Need to create the UDP socket here?

			printer.print("Session with " + relevantData + " created.");
			break;
		}
		case (NOT_LOGGED_IN):
		{
			printer.print("You are not logged in.");
			break;
		}
		case (ALREADY_BUSY):
		{
			printer.print("You are already participating in a session or room.");
			break;
		}
		case (SESSION_WITH_SELF):
		{
			printer.print("You can't create a session with yourself, " + relevantData + "!");
			break;
		}
		case (USER_NOT_FOUND):
		{
			printer.print(relevantData + " is either logged off or does not exist.");
			break;
		}
		case (OTHER_USER_BUSY):
		{
			printer.print(relevantData + " is busy.");
			break;
		}
		case (OPEN_ROOM_SUCCESS):
		{
			printer.print("Room '" + relevantData + "' created.");
			break;
		}
		case (ROOM_NAME_EXISTS):
		{
			printer.print("A room named " + relevantData + " already exists.");
			break;
		}
		case (JOIN_ROOM_SUCCESS):
		{
			printer.print("You have joined '" + relevantData + "'.");
			break;
		}
		case (ROOM_DOES_NOT_EXIST):
		{
			printer.print("There is no room named '" + relevantData + "'.");
			break;
		}
		case (EXIT_ROOM_SUCCESS):
		{
			printer.print("You have left the room.");
			break;
		}
		case (CLOSE_SESSION_SUCCESS):
		{
			printer.print("Session closed.");
			break;
		}
		case (NOT_IN_SESSION_OR_ROOM):
		{
			printer.print("You are not in a session or room.");
			break;
		}
		case (CLOSE_ROOM_SUCCESS):
		{
			printer.print("You have closed the room named '" + relevantData + "'.");
			break;
		}
		case (NOT_ROOM_OWNER):
		{
			printer.print("You are not the room owner.");
			break;
		}
		case (DISCONNECT_SUCCESS):
		{
			printer.print("Disconnected from server.");

			// Close the socket
			srvConnection.closeSocket();
			connected = false;

			break;
		}
		case (GET_REGISTERED_USERS):
		{
			// Get the number of registered users first
			int usersNumber = atoi(srvConnection.receiveMessage().c_str());

			if (usersNumber > 0)
			{
				printer.print("Registered Users:");

				for (int i = 0; i < usersNumber; i++)
				{
					// Receive the current user name
					printer.print(srvConnection.receiveMessage());
				}
			}
			else
			{
				printer.print("There are no registered users.");
			}

			break;
		}
		case (GET_CONNECTED_USERS):
		{
			// Get the number of connected users first
			int usersNumber = atoi(srvConnection.receiveMessage().c_str());

			if (usersNumber > 0)
			{
				printer.print("Connected Users:");

				for (int i = 0; i < usersNumber; i++)
				{
					// Receive the current user name
					printer.print(srvConnection.receiveMessage());
				}
			}
			else
			{
				printer.print("There are no connected users.");
			}

			break;
		}
		case (GET_CHAT_ROOMS):
		{
			// Get the number of rooms first
			int roomsNumber = atoi(srvConnection.receiveMessage().c_str());

			if (roomsNumber > 0)
			{
				printer.print("Open chat-rooms:");

				for (int i = 0; i < roomsNumber; i++)
				{
					// Receive the current room name
					printer.print(srvConnection.receiveMessage());
				}
			}
			else
			{
				printer.print("There are no open chat-rooms.");
			}

			break;
		}
		case (GET_USERS_IN_CHAT_ROOM):
		{
			// Get the number of users in the room first
			int usersNumber = atoi(srvConnection.receiveMessage().c_str());

			if (usersNumber > 0)
			{
				printer.print("Users connected to '" + relevantData + "':");

				for (int i = 0; i < usersNumber; i++)
				{
					// Receive the current user
					printer.print(srvConnection.receiveMessage());
				}
			}
			else
			{
				printer.print("There are no users in the room '" + relevantData + "'.");
			}

			break;
		}
		case (STATUS_FREE):
		{
			printer.print("You are logged in, but not in a room/session.");
			break;
		}
		case (STATUS_IN_A_ROOM):
		{
			printer.print("You are in a room.");
			break;
		}
		case (STATUS_IN_A_SESSION):
		{
			printer.print("You are in a session.");
			break;
		}
		default:
		{
			printer.print("Unknown reply-code.");
		}
	}
}

void ClientController::connect(string address)
{
	// TODO: TCPProtocol
	int MSGPORT = 3346;

	// Create a socket to the address
	srvConnection.openSocket(address, MSGPORT);

	// Receive reply from server
	int replyCode = srvConnection.receiveReplyCode();

	manageReply(replyCode, address);
}

void ClientController::login(string username, string password)
{
// TODO: Get this from TCPProtocol
unsigned int LOGINz = 70;

	// Send the LOGIN command
	srvConnection.sendCommandCode(LOGINz);

	// Send the username and password
	srvConnection.sendArgs(username + " " + password);

	// Receive reply from server
	int replyCode = srvConnection.receiveReplyCode();

	manageReply(replyCode, username);
}

void ClientController::registerUser(string username, string password)
{
	// TODO: Get this from TCPProtocol
	unsigned int REGISTERz = 71;

	// Send the REGISTER command
	srvConnection.sendCommandCode(REGISTERz);

	// Send the username and password
	srvConnection.sendArgs(username + " " + password);

	// Receive reply from server
	int replyCode = srvConnection.receiveReplyCode();

	manageReply(replyCode, username);
}

void ClientController::openSession(string otherUserName)
{
	// TODO: Get this from TCPProtocol
	unsigned int OPEN_SESSION_WITH_PEER = 2;

	// Send the OPEN_SESSION command
	srvConnection.sendCommandCode(OPEN_SESSION_WITH_PEER);

	// Send the username to open a session with
	srvConnection.sendArgs(otherUserName);

	// Receive reply from server
	int replyCode = srvConnection.receiveReplyCode();

	manageReply(replyCode, otherUserName);
}

void ClientController::openRoom(string roomName)
{
	// TODO: Get this from TCPProtocol
	unsigned int OPEN_CHAT_ROOMz = 11;
	int EXPECTED_COMMAND_BYTES_SIZE = 4;

	// Send the OPEN_ROOM command
	srvConnection.sendCommandCode(OPEN_CHAT_ROOMz);

	// Send the room name
	srvConnection.sendArgs(roomName);

	// Receive reply from server
	int replyCode = srvConnection.receiveReplyCode();

	manageReply(replyCode, roomName);
}

void ClientController::joinRoom(string roomName)
{
	// TODO: Get this from TCPProtocol
	unsigned int JOIN_CHAT_ROOMz = 14;

	// Send the JOIN_ROOM command
	srvConnection.sendCommandCode(JOIN_CHAT_ROOMz);

	// Send the room name
	srvConnection.sendArgs(roomName);

	// Receive reply from server
	int replyCode = srvConnection.receiveReplyCode();

	manageReply(replyCode, roomName);
}

void ClientController::closeSessionOrExitRoom()
{
	// TODO: TCPProtocol
	int CLOSE_SESSION_OR_EXIT_ROOMz = 15;

	// Send the CLOSE_SESSION_OR_EXIT_ROOM command
	srvConnection.sendCommandCode(CLOSE_SESSION_OR_EXIT_ROOMz);

	// Receive reply from server
	int replyCode = srvConnection.receiveReplyCode();

	manageReply(replyCode, "");
}

void ClientController::closeRoom(string roomName)
{
	// TODO: Get this from TCPProtocol
	unsigned int CLOSE_ROOMz = 16;

	// Send the CLOSE_ROOM command
	srvConnection.sendCommandCode(CLOSE_ROOMz);

	// Send the room name
	srvConnection.sendArgs(roomName);

	// Receive reply from server
	int replyCode = srvConnection.receiveReplyCode();

	manageReply(replyCode, roomName);
}

void ClientController::disconnect()
{
	// TODO: TCPProtocol
	int DISCONNECTz = 13;

	// Send the DISCONNECT command
	srvConnection.sendCommandCode(DISCONNECTz);

	// Receive reply from server
	int replyCode = srvConnection.receiveReplyCode();

	manageReply(replyCode, "");
}

void ClientController::requestAllRegisterdUsersName()
{
	// TODO: TCPProtocolz
	const int GET_REGISTERED_USERS = 7;

	srvConnection.sendCommandCode(GET_REGISTERED_USERS);

	// Receive reply from server
	int replyCode = srvConnection.receiveReplyCode();

	manageReply(replyCode, "");
}

void ClientController::requestAllConnectedUsersName()
{
	// TODO: TCPProtocolz
	const int GET_CONNECTED_USERS = 8;

	srvConnection.sendCommandCode(GET_CONNECTED_USERS);

	// Receive reply from server
	int replyCode = srvConnection.receiveReplyCode();

	manageReply(replyCode, "");
}

void ClientController::requestAllRooms()
{
	// TODO: TCPProtocolz
	const int GET_CHAT_ROOMS = 9;

	srvConnection.sendCommandCode(GET_CHAT_ROOMS);

	// Receive reply from server
	int replyCode = srvConnection.receiveReplyCode();

	manageReply(replyCode, "");
}

void ClientController::requestAllUsersInRoom(string roomName)
{
	// TODO: TCPProtocolz
	const int GET_USERS_IN_CHAT_ROOM = 10;

	// Send the command-code and the room name
	srvConnection.sendCommandCode(GET_USERS_IN_CHAT_ROOM);
	srvConnection.sendArgs(roomName);

	// Receive reply from server
	int replyCode = srvConnection.receiveReplyCode();

	manageReply(replyCode, roomName);
}

void ClientController::requestStatus()
{
	// TODO: TCPProtocolz
	const int GET_STATUS = 17;

	// Send the command-code
	srvConnection.sendCommandCode(GET_STATUS);

	// Receive reply from server
	int replyCode = srvConnection.receiveReplyCode();

	manageReply(replyCode, "");
}

