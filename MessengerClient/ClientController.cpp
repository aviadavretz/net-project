
/*
 * ClientController.cpp
 *
 *  Created on: Feb 27, 2017
 *      Author: user
 */

#include "ClientController.h"

ClientController::ClientController() : connected(false), listener(NULL)
{
}

bool ClientController::isConnected()
{
	return connected;
}

void ClientController::sendCommandToServer(int commandCode, string args)
{
	// Send the command to the server
	srvConnection.sendCommandCode(commandCode);

	// Send additional arguments to the server
	srvConnection.sendArgs(args);
}

void ClientController::sendCommandToServer(int commandCode)
{
	// Send the command to the server
	srvConnection.sendCommandCode(commandCode);
}

void ClientController::connect(string address)
{
	// Create a socket to the address
	srvConnection.openSocket(address, MSNGR_PORT);

	// Get the server reply
	int replyCode = srvConnection.receiveReplyCode();

	if (replyCode == CONNECT_SUCCESS)
	{
		printer.print("Connected to the server!");
		connected = true;

		// Start listening for server responses
		listener = new ServerRepliesListener(&srvConnection, &printer, this);
		listener->start();
	}
	else
	{
		printer.print("Connection failed !");
	}
}

void ClientController::login(string username, string password)
{
	// Send login command to the server with username and password
	sendCommandToServer(LOGIN, username + " " + password);
}

void ClientController::registerUser(string username, string password)
{
	// Send register command to the server with username and password
	sendCommandToServer(REGISTER, username + " " + password);
}

void ClientController::openSession(string otherUserName)
{
	// Send open session command to the server with the username we want the session with
	sendCommandToServer(OPEN_SESSION_WITH_PEER, otherUserName);
}

void ClientController::openRoom(string roomName)
{
	// Send open chat room command to the server with the room's name
	sendCommandToServer(OPEN_CHAT_ROOM, roomName);
}

void ClientController::joinRoom(string roomName)
{
	// Send join chat room command with the room's name
	sendCommandToServer(JOIN_CHAT_ROOM, roomName);
}

void ClientController::closeSessionOrExitRoom()
{
	// Send close session or exit room command to the server
	sendCommandToServer(CLOSE_SESSION_OR_EXIT_ROOM);
}

void ClientController::closeRoom(string roomName)
{
	// Send close room command to the server with the room's name
	sendCommandToServer(CLOSE_ROOM, roomName);
}

void ClientController::disconnect()
{
	// Send disconnect command to the server
	sendCommandToServer(DISCONNECT);
}

void ClientController::requestAllRegisterdUsersName()
{
	// Send get registered users command to the server
	sendCommandToServer(GET_REGISTERED_USERS);
}

void ClientController::requestAllConnectedUsersName()
{
	// Send get connected users command to the server
	sendCommandToServer(GET_CONNECTED_USERS);
}

void ClientController::requestAllRooms()
{
	// Send get chat rooms command to the server
	sendCommandToServer(GET_CHAT_ROOMS);
}

void ClientController::requestAllUsersInRoom(string roomName)
{
	// Send get users in chat room command to the server with the room's name
	sendCommandToServer(GET_USERS_IN_CHAT_ROOM, roomName);
}

void ClientController::requestStatus()
{
	// Send get status command to the server
	sendCommandToServer(GET_STATUS);
}

void ClientController::notifyDisconnected()
{
	// Stop listening for server responses
	listener->stop();

	// Close the socket
	srvConnection.closeSocket();

	connected = false;

	printer.print("Disconnected from server.");
}

void ClientController::notifySessionEstablished()
{
	// Receive the relevant data from the server.
	string otherUsername = srvConnection.receiveMessage();
	string otherUserAddr = srvConnection.receiveMessage();

	// TODO: Open socket
//	// TODO: Move this to TCPProtocol
//	int SESSION_PORT = 3434;
//	UDPSocket* sessionSocket = new UDPSocket(otherUserAddr, SESSION_PORT);

	printer.print("Session with " + otherUsername + " (" + otherUserAddr + ") established.");
}

void ClientController::notifyChatRoomOpened()
{
	// Receive the relevant data from the server.
	string roomName = srvConnection.receiveMessage();

	printer.print("ChatRoom '" + roomName + "' created.");
}

void ClientController::notifyJoinedRoom()
{
	printer.print("Establishing connections...");

	string currentUserAddress = srvConnection.receiveMessage();

	// Get all the users' connection data ,and add another UDP socket for each
	// While we haven't received the DONE_SENDING_ROOM_PARTICIPANTS code
	while (currentUserAddress.compare(DONE_SENDING_ROOM_PARTICIPANTS) != 0)
	{
		// TODO: Add a UDPSocket

		// Get the next user address
		currentUserAddress = srvConnection.receiveMessage();
	}

	printer.print("All connections established. You have joined the room.");
}

void ClientController::notifySomeoneJoinedRoom()
{
	// Receive the relevant data from the server.
	string joiningUsername = srvConnection.receiveMessage();
	string joininguserAddr = srvConnection.receiveMessage();

	// TODO: Add another UDP socket

	printer.print(joiningUsername + " has joined the room.");
}

void ClientController::notifySomeoneLeftRoom()
{
	// Receive the relevant data from the server.
	string exitingUsername = srvConnection.receiveMessage();

	// TODO: Close the relevant socket

	printer.print(exitingUsername + " has left the room.");
}

void ClientController::notifyExitRoom()
{
	// TODO: Close all UDP sockets

	printer.print("You have left the room.");
}

void ClientController::notifySessionClosed()
{
	// Receive the relevant data from the server.
	string otherUsername = srvConnection.receiveMessage();

	// TODO: Close socket

	printer.print("Session with " + otherUsername + " has ended.");
}

void ClientController::notifyRoomClosedByOwner()
{
	// Receive the relevant data from the server.
	string roomName = srvConnection.receiveMessage();

	// TODO: Close all UDP sockets

	printer.print("ChatRoom '" + roomName + "' closed by its owner.");
}

void ClientController::notifyRoomClosedSuccess()
{
	printer.print("Closing the room..");
}

ServerRepliesObserver::~ServerRepliesObserver() {}

