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
			closeSocket();
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

	// Create a socket to the address
	socketToServer = new TCPSocket(address, MSGPORT);

	// Receive reply from server
	int replyCode = receiveReplyCode();

	manageReply(replyCode, address);
}

void ClientController::login(string username, string password)
{
// TODO: Get this from TCPProtocol
unsigned int LOGINz = 70;

	// Send the LOGIN command
	sendCommandCode(LOGINz);

	// Send the username and password
	sendArgs(username + " " + password);

	// Receive reply from server
	int replyCode = receiveReplyCode();

	manageReply(replyCode, username);
}

void ClientController::registerUser(string username, string password)
{
	// TODO: Get this from TCPProtocol
	unsigned int REGISTERz = 71;

	// Send the REGISTER command
	sendCommandCode(REGISTERz);

	// Send the username and password
	sendArgs(username + " " + password);

	// Receive reply from server
	int replyCode = receiveReplyCode();

	manageReply(replyCode, username);
}

void ClientController::openSession(string otherUserName)
{
	// TODO: Get this from TCPProtocol
	unsigned int OPEN_SESSION_WITH_PEER = 2;

	// Send the OPEN_SESSION command
	sendCommandCode(OPEN_SESSION_WITH_PEER);

	// Send the username to open a session with
	sendArgs(otherUserName);

	// Receive reply from server
	int replyCode = receiveReplyCode();

	manageReply(replyCode, otherUserName);
}

void ClientController::openRoom(string roomName)
{
	// TODO: Get this from TCPProtocol
	unsigned int OPEN_CHAT_ROOMz = 11;
	int EXPECTED_COMMAND_BYTES_SIZE = 4;

	// Send the OPEN_ROOM command
	sendCommandCode(OPEN_CHAT_ROOMz);

	// Send the room name
	sendArgs(roomName);

	// Receive reply from server
	int replyCode = receiveReplyCode();

	manageReply(replyCode, roomName);
}

void ClientController::joinRoom(string roomName)
{
	// TODO: Get this from TCPProtocol
	unsigned int JOIN_CHAT_ROOMz = 14;

	// Send the JOIN_ROOM command
	sendCommandCode(JOIN_CHAT_ROOMz);

	// Send the room name
	sendArgs(roomName);

	// Receive reply from server
	int replyCode = receiveReplyCode();

	manageReply(replyCode, roomName);
}

void ClientController::closeSessionOrExitRoom()
{
	// TODO: TCPProtocol
	int CLOSE_SESSION_OR_EXIT_ROOMz = 15;

	// Send the CLOSE_SESSION_OR_EXIT_ROOM command
	sendCommandCode(CLOSE_SESSION_OR_EXIT_ROOMz);

	// Receive reply from server
	int replyCode = receiveReplyCode();

	manageReply(replyCode, "");
}

void ClientController::closeRoom(string roomName)
{
	// TODO: Get this from TCPProtocol
	unsigned int CLOSE_ROOMz = 16;

	// Send the CLOSE_ROOM command
	sendCommandCode(CLOSE_ROOMz);

	// Send the room name
	sendArgs(roomName);

	// Receive reply from server
	int replyCode = receiveReplyCode();

	manageReply(replyCode, roomName);
}

void ClientController::disconnect()
{
	// TODO: TCPProtocol
	int DISCONNECTz = 13;

	// Send the DISCONNECT command
	sendCommandCode(DISCONNECTz);

	// Receive reply from server
	int replyCode = receiveReplyCode();

	manageReply(replyCode, "");
}

int ClientController::receiveReplyCode()
{
	// TODO: TCPProtocol
	int EXPECTED_COMMAND_BYTES_SIZE = 4;

	// Receive reply (the size should be as stated in the protocol)
	int reply = 0;
	int bytesReceived = socketToServer->recv((char*)&reply, EXPECTED_COMMAND_BYTES_SIZE);
	int returnedCode = ntohl(reply);

	return returnedCode;
}

void ClientController::sendCommandCode(int commandCode)
{
	// Send the command-code
	int commandLength = htonl(commandCode);
	socketToServer->send((char*)&commandLength,4);
}

void ClientController::sendArgs(string message)
{
	// Send the arguments as a single message
	int messageLength = htonl(message.length());

	// Send the message length first
	socketToServer->send((char*)&messageLength, 4);

	// Send the message itself
	socketToServer->send(message);
}

void ClientController::closeSocket()
{
	socketToServer->close();
	socketToServer = NULL;
}


