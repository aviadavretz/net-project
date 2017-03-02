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
	// TCPProtocol
	const int CONNECT_SUCCESS = 420;

	const int LOGIN_SUCCEEDED = 202;
	const int ALREADY_LOGGED_IN = 200;
	const int BAD_USERNAME_PASSWORD = 201;

	const int REGISTER_FAILURE = 203;
	const int REGISTER_SUCCEEDED = 204;
	const int USERNAME_EXISTS = 205;

	const int SESSION_ESTABLISHED = 6;
	const int NOT_LOGGED_IN = 206;
	const int ALREADY_BUSY = 462;
	const int USER_NOT_FOUND = 522;
	const int OTHER_USER_BUSY = 523;

	const int OPEN_ROOM_SUCCESS = 440;
	const int ROOM_NAME_EXISTS = 441;

	const int JOIN_ROOM_SUCCESS = 460;
	const int ROOM_DOES_NOT_EXIST = 461;

	const int EXIT_ROOM_SUCCESS = 480;
	const int NOT_IN_SESSION_OR_ROOM = 481;
	const int CLOSE_SESSION_SUCCESS = 490;

	const int CLOSE_ROOM_SUCCESS = 500;
	const int NOT_ROOM_OWNER = 501;

	const int DISCONNECT_SUCCESS = 421;

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
		case (ALREADY_LOGGED_IN):
		{
			printer.print("You are already logged in.");
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
			socket->close();
			socket = NULL;
			connected = false;

			break;
		}
		default:
		{
			printer.print("Unknown error. ");
		}
	}
}

void ClientController::connect(string address)
{
	// TODO: TCPProtocol
	int MSGPORT = 3346;
	int EXPECTED_COMMAND_BYTES_SIZE = 4;
//	const int CONNECT_SUCCESS = 420;

	// Create a socket to the address
	socket = new TCPSocket(address, MSGPORT);

	int reply = 0;

	// Receive reply (the size should be as stated in the protocol)
	int bytesReceived = socket->recv((char*)&reply, EXPECTED_COMMAND_BYTES_SIZE);

	int returnedCode = ntohl(reply);

	manageReply(returnedCode, address);

//	if (returnedCode == CONNECT_SUCCESS)
//	{
//		printer.print("Connected to " + address);
//		connected = true;
//	}
}

void ClientController::login(string username, string password)
{
// TODO: Get this from TCPProtocol
unsigned int LOGINz = 70;
const int EXPECTED_COMMAND_BYTES_SIZE = 4;
//const int LOGIN_SUCCEEDED = 202;
//const int ALREADY_LOGGED_IN = 200;
//const int BAD_USERNAME_PASSWORD = 201;

	// Send the LOGIN command
	int commandLength = htonl(LOGINz);
	socket->send((char*)&commandLength,4);

	string message = username + " " + password;

	printer.print("Trying to login: " + message);

	// Send the username and password
	int messageLength = htonl(message.length());
	socket->send((char*)&messageLength, 4);
	socket->send(message);

	int reply = 0;

	// Receive reply (the size should be as stated in the protocol)
	int bytesReceived = socket->recv((char*)&reply, EXPECTED_COMMAND_BYTES_SIZE);

	int returnedCode = ntohl(reply);

	manageReply(returnedCode, username);
}

void ClientController::registerUser(string username, string password)
{
	// TODO: Get this from TCPProtocol
	unsigned int REGISTERz = 71;
	int EXPECTED_COMMAND_BYTES_SIZE = 4;

//	const int ALREADY_LOGGED_IN = 200;
//	const int REGISTER_FAILURE = 203;
//	const int REGISTER_SUCCEEDED = 204;
//	const int USERNAME_EXISTS = 205;

	// Send the REGISTER command
	int commandLength = htonl(REGISTERz);
	socket->send((char*)&commandLength,4);

	string message = username + " " + password;

	printer.print("Trying to register: " + message);

	// Send the username and password
	int messageLength = htonl(message.length());
	socket->send((char*)&messageLength, 4);
	socket->send(message);

	int reply = 0;

	// Receive reply (the size should be as stated in the protocol)
	int bytesReceived = socket->recv((char*)&reply, EXPECTED_COMMAND_BYTES_SIZE);
	int returnedCode = ntohl(reply);

	manageReply(returnedCode, username);
}

void ClientController::openSession(string otherUserName)
{
	// TODO: Get this from TCPProtocol
//	int SESSION_ESTABLISHED = 6;
//	int NOT_LOGGED_IN = 206;
//	int ALREADY_BUSY = 462;
//	int USER_NOT_FOUND = 522;
//	int OTHER_USER_BUSY = 523;
	unsigned int OPEN_SESSION_WITH_PEER = 2;
	int EXPECTED_COMMAND_BYTES_SIZE = 4;

	// Send the OPEN_SESSION command
	int commandLength = htonl(OPEN_SESSION_WITH_PEER);
	socket->send((char*)&commandLength,4);

	// Send the username to open session with
	int messageLength = htonl(otherUserName.length());
	socket->send((char*)&messageLength, 4);
	socket->send(otherUserName);

	int reply = 0;

	// Receive reply (the size should be as stated in the protocol)
	int bytesReceived = socket->recv((char*)&reply, EXPECTED_COMMAND_BYTES_SIZE);
	int returnedCode = ntohl(reply);

	manageReply(reply, otherUserName);

//	if (returnedCode == SESSION_ESTABLISHED)
//	{
//		printer.print("Session with " + otherUserName + " created.");
//
//		// TODO: Need to create the UDP socket here?
//	}
//	else if (returnedCode == NOT_LOGGED_IN)
//	{
//		printer.print("You are not logged in.");
//	}
//	else if (returnedCode == ALREADY_BUSY)
//	{
//		printer.print("You are already participating in a Session or ChatRoom.");
//	}
//	else if (returnedCode == USER_NOT_FOUND)
//	{
//		printer.print(otherUserName + " is either logged off or does not exist.");
//	}
//	else if (returnedCode == OTHER_USER_BUSY)
//	{
//		printer.print(otherUserName + " is busy.");
//	}
}

void ClientController::openRoom(string roomName)
{
	// TODO: Get this from TCPProtocol
//	int OPEN_ROOM_SUCCESS = 440;
//	int NOT_LOGGED_IN = 206;
//	int ROOM_NAME_EXISTS = 441;
	unsigned int OPEN_CHAT_ROOMz = 11;
	int EXPECTED_COMMAND_BYTES_SIZE = 4;

	// Send the OPEN_ROOM command
	int commandLength = htonl(OPEN_CHAT_ROOMz);
	socket->send((char*)&commandLength,4);

	// Send the room name
	int messageLength = htonl(roomName.length());
	socket->send((char*)&messageLength, 4);
	socket->send(roomName);

	int reply = 0;

	// Receive reply (the size should be as stated in the protocol)
	int bytesReceived = socket->recv((char*)&reply, EXPECTED_COMMAND_BYTES_SIZE);
	int returnedCode = ntohl(reply);

	manageReply(returnedCode, roomName);

//	if (returnedCode == OPEN_ROOM_SUCCESS)
//	{
//		printer.print("Room '" + roomName + "' created.");
//	}
//	else if (returnedCode == NOT_LOGGED_IN)
//	{
//		printer.print("You are not logged in.");
//	}
//	else if (returnedCode == ROOM_NAME_EXISTS)
//	{
//		printer.print("A room with that name already exists.");
//	}
}

void ClientController::joinRoom(string roomName)
{
	// TODO: Get this from TCPProtocol
//	int JOIN_ROOM_SUCCESS = 460;
//	int NOT_LOGGED_IN = 206;
//	int ROOM_DOES_NOT_EXIST = 461;
//	int ALREADY_BUSY = 462;
	unsigned int JOIN_CHAT_ROOMz = 14;
	int EXPECTED_COMMAND_BYTES_SIZE = 4;

	// Send the JOIN_ROOM command
	int commandLength = htonl(JOIN_CHAT_ROOMz);
	socket->send((char*)&commandLength,4);

	// Send the room name
	int messageLength = htonl(roomName.length());
	socket->send((char*)&messageLength, 4);
	socket->send(roomName);

	int reply = 0;

	// Receive reply (the size should be as stated in the protocol)
	int bytesReceived = socket->recv((char*)&reply, EXPECTED_COMMAND_BYTES_SIZE);
	int returnedCode = ntohl(reply);

	manageReply(returnedCode, roomName);

//	if (returnedCode == JOIN_ROOM_SUCCESS)
//	{
//		printer.print("You have joined '" + roomName + "'.");
//	}
//	else if (returnedCode == NOT_LOGGED_IN)
//	{
//		printer.print("You are not logged in.");
//	}
//	else if (returnedCode == ROOM_DOES_NOT_EXIST)
//	{
//		printer.print("There is no room named '" + roomName + "'.");
//	}
//	else if (returnedCode == ALREADY_BUSY)
//	{
//		printer.print("You are already inside a room or session.");
//	}
}

void ClientController::closeSessionOrExitRoom()
{
	// TODO: TCPProtocol
	int EXPECTED_COMMAND_BYTES_SIZE = 4;
	int CLOSE_SESSION_OR_EXIT_ROOMz = 15;
//	int NOT_LOGGED_IN = 206;
//	int EXIT_ROOM_SUCCESS = 480;
//	int NOT_IN_SESSION_OR_ROOM = 481;
//	int CLOSE_SESSION_SUCCESS = 490;

	// Send the CLOSE_SESSION_OR_EXIT_ROOM command
	int commandLength = htonl(CLOSE_SESSION_OR_EXIT_ROOMz);
	socket->send((char*)&commandLength,4);

	int reply = 0;

	// Receive reply (the size should be as stated in the protocol)
	int bytesReceived = socket->recv((char*)&reply, EXPECTED_COMMAND_BYTES_SIZE);
	int returnedCode = ntohl(reply);

	manageReply(returnedCode, "");

//	if (returnedCode == EXIT_ROOM_SUCCESS)
//	{
//		printer.print("You have left the room.");
//	}
//	else if (returnedCode == CLOSE_SESSION_SUCCESS)
//	{
//		printer.print("Session closed.");
//	}
//	else if (returnedCode == NOT_IN_SESSION_OR_ROOM)
//	{
//		printer.print("You are not in a ChatRoom or a Session.");
//	}
//	else if (returnedCode == NOT_LOGGED_IN)
//	{
//		printer.print("You are not logged in.");
//	}
}

void ClientController::closeRoom(string roomName)
{
	// TODO: Get this from TCPProtocol
//	int CLOSE_ROOM_SUCCESS = 500;
//	int NOT_LOGGED_IN = 206;
//	int ROOM_DOES_NOT_EXIST = 461;
//	int NOT_ROOM_OWNER = 501;
	unsigned int CLOSE_ROOMz = 16;
	int EXPECTED_COMMAND_BYTES_SIZE = 4;

	// Send the CLOSE_ROOM command
	int commandLength = htonl(CLOSE_ROOMz);
	socket->send((char*)&commandLength,4);

	// Send the room name
	int messageLength = htonl(roomName.length());
	socket->send((char*)&messageLength, 4);
	socket->send(roomName);

	int reply = 0;

	// Receive reply (the size should be as stated in the protocol)
	int bytesReceived = socket->recv((char*)&reply, EXPECTED_COMMAND_BYTES_SIZE);
	int returnedCode = ntohl(reply);

	manageReply(returnedCode, roomName);

//	if (returnedCode == CLOSE_ROOM_SUCCESS)
//	{
//		printer.print("You have closed '" + roomName + "'.");
//	}
//	else if (returnedCode == NOT_LOGGED_IN)
//	{
//		printer.print("You are not logged in.");
//	}
//	else if (returnedCode == ROOM_DOES_NOT_EXIST)
//	{
//		printer.print("There is no room named '" + roomName + "'.");
//	}
//	else if (returnedCode == NOT_ROOM_OWNER)
//	{
//		printer.print("You are not the room owner.");
//	}
}

void ClientController::disconnect()
{
	// TODO: TCPProtocol
	int EXPECTED_COMMAND_BYTES_SIZE = 4;
//	int DISCONNECT_SUCCESS = 421;
	int DISCONNECTz = 13;

	// Send the DISCONNECT command
	int commandLength = htonl(DISCONNECTz);
	socket->send((char*)&commandLength,4);

	int reply = 0;

	// Receive reply (the size should be as stated in the protocol)
	int bytesReceived = socket->recv((char*)&reply, EXPECTED_COMMAND_BYTES_SIZE);
	int returnedCode = ntohl(reply);

	manageReply(returnedCode, "");

//	if (returnedCode == DISCONNECT_SUCCESS)
//	{
//		printer.print("Disconnected from server.");
//
//		socket->close();
//		socket = NULL;
//
//		connected = false;
//	}
}


