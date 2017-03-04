
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

int ClientController::sendCommandWithArgsToServerAndReceiveReply(int commandCode, string args)
{
	// Send the command to the server
	srvConnection.sendCommandCode(commandCode);

	// Send additional arguments to the server
	srvConnection.sendArgs(args);

	// Return the reply from the server
	return srvConnection.receiveReplyCode();
}

int ClientController::sendCommandToServerAndReceiveReply(int commandCode)
{
	// Send the command to the server
	srvConnection.sendCommandCode(commandCode);

	// Return the reply from the ser
	return srvConnection.receiveReplyCode();
}

void ClientController::connect(string address)
{
	// Create a socket to the address
	srvConnection.openSocket(address, MSNGR_PORT);

	// Receive reply from server
	int replyCode = srvConnection.receiveReplyCode();

	if (replyCode == CONNECT_SUCCESS)
	{
		connected = true;
	}

	printer.printServerReplyMessage(replyCode, address);
}

void ClientController::login(string username, string password)
{
	// Send login command to the server with username and password
	int replyCode = sendCommandWithArgsToServerAndReceiveReply(LOGIN, username + " " + password);

	printer.printServerReplyMessage(replyCode, username);
}

void ClientController::registerUser(string username, string password)
{
	// Send register command to the server with username and password
	int replyCode = sendCommandWithArgsToServerAndReceiveReply(REGISTER, username + " " + password);

	printer.printServerReplyMessage(replyCode, username);
}

void ClientController::openSession(string otherUserName)
{
	// Send open session command to the server with the username we want the session with
	int replyCode = sendCommandWithArgsToServerAndReceiveReply(OPEN_SESSION_WITH_PEER, otherUserName);

	if (replyCode == SESSION_ESTABLISHED)
	{
		// TODO: Need to create the UDP socket here?
	}
	else
	{
		printer.printServerReplyMessage(replyCode, otherUserName);
	}
}

void ClientController::openRoom(string roomName)
{
	// Send open chat room command to the server with the room's name
	int replyCode = sendCommandWithArgsToServerAndReceiveReply(OPEN_CHAT_ROOM, roomName);

	if (replyCode == OPEN_CHAT_ROOM_SUCCESS)
	{
		// TODO : Some additional steps should be taken
	}
	else
	{
		printer.printServerReplyMessage(replyCode, roomName);
	}
}

void ClientController::joinRoom(string roomName)
{
	// Send join chat room command with the room's name
	int replyCode = sendCommandWithArgsToServerAndReceiveReply(JOIN_CHAT_ROOM, roomName);

	if (replyCode == JOIN_ROOM_SUCCESS)
	{
		// TODO : Some additional steps should be taken
	}
	else
	{
		printer.printServerReplyMessage(replyCode, roomName);
	}
}

void ClientController::closeSessionOrExitRoom()
{
	// Send close session or exit room command to the server
	int replyCode = sendCommandToServerAndReceiveReply(CLOSE_SESSION_OR_EXIT_ROOM);

	if (replyCode == EXIT_ROOM_SUCCESS)
	{
		// TODO : Do something to exit the room
	}
	else if (replyCode == CLOSE_SESSION_SUCCESS)
	{
		// TODO : Do something to close the session
	}
	else
	{
		printer.printServerReplyMessage(replyCode);
	}
}

void ClientController::closeRoom(string roomName)
{
	// Send close room command to the server with the room's name
	int replyCode = sendCommandWithArgsToServerAndReceiveReply(CLOSE_ROOM, roomName);

	if (replyCode == CLOSE_ROOM_SUCCESS)
	{
		// TODO : Do something to exit the room
	}
	else
	{
		printer.printServerReplyMessage(replyCode, roomName);
	}
}

void ClientController::disconnect()
{
	// Send disconnect command to the server
	int replyCode = sendCommandToServerAndReceiveReply(DISCONNECT);

	if (replyCode == DISCONNECT_SUCCESS)
	{
		// Close the socket
		srvConnection.closeSocket();
		connected = false;

		printer.print("Disconnected from server.");
	}
	else
	{
		printer.printServerReplyMessage(replyCode);
	}
}

void ClientController::requestAllRegisterdUsersName()
{
	// Send get registered users command to the server
	int replyCode = sendCommandToServerAndReceiveReply(GET_REGISTERED_USERS);

	if (replyCode == GET_REGISTERED_USERS)
	{
		// Get the number of registered users first
		int usersNumber = atoi(srvConnection.receiveMessage().c_str());

		if (usersNumber > 0)
		{
			printer.printRegisteredUsers(srvConnection.receiveMessages(usersNumber));
		}
		else
		{
			printer.print("There are no registered users.");
		}
	}
	else
	{
		printer.printServerReplyMessage(replyCode);
	}
}

void ClientController::requestAllConnectedUsersName()
{
	// Send get connected users command to the server
	int replyCode = sendCommandToServerAndReceiveReply(GET_CONNECTED_USERS);

	if (replyCode == GET_CONNECTED_USERS)
	{
		// Get the number of connected users first
		int usersNumber = atoi(srvConnection.receiveMessage().c_str());

		if (usersNumber > 0)
		{
			printer.printConnectedUsers(srvConnection.receiveMessages(usersNumber));
		}
		else
		{
			printer.print("There are no connected users.");
		}
	}
	else
	{
		printer.printServerReplyMessage(replyCode);
	}
}

void ClientController::requestAllRooms()
{
	// Send get chat rooms command to the server
	int replyCode = sendCommandToServerAndReceiveReply(GET_CHAT_ROOMS);

	if (replyCode == GET_CHAT_ROOMS)
	{
		// Get the number of rooms first
		int roomsNumber = atoi(srvConnection.receiveMessage().c_str());

		if (roomsNumber > 0)
		{
			printer.printRooms(srvConnection.receiveMessages(roomsNumber));
		}
		else
		{
			printer.print("There are no open chat-rooms.");
		}
	}
	else
	{
		printer.printServerReplyMessage(replyCode);
	}
}

void ClientController::requestAllUsersInRoom(string roomName)
{
	// Send get users in chat room command to the server with the room's name
	int replyCode = sendCommandWithArgsToServerAndReceiveReply(GET_USERS_IN_CHAT_ROOM, roomName);

	if (replyCode == GET_USERS_IN_CHAT_ROOM)
	{
		// Get the number of users in the room first
		int usersNumber = atoi(srvConnection.receiveMessage().c_str());

		if (usersNumber > 0)
		{
			printer.printUsersInRoom(srvConnection.receiveMessages(usersNumber), roomName);
		}
		else
		{
			printer.print("There are no users in the room '" + roomName + "'.");
		}
	}
	else
	{
		printer.printServerReplyMessage(replyCode, roomName);
	}
}

void ClientController::requestStatus()
{
	// Send get status command to the server
	int replyCode = sendCommandToServerAndReceiveReply(GET_STATUS);

	printer.printServerReplyMessage(replyCode);
}

