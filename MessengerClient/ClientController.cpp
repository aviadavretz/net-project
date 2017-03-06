
/*
 * ClientController.cpp
 *
 *  Created on: Feb 27, 2017
 *      Author: user
 */

#include "ClientController.h"

ClientController::ClientController() : connected(false), srvListener(NULL), peerListener(NULL) {}

bool ClientController::isConnected()
{
	return connected;
}

void ClientController::notifyMessageReceived(string username, string message)
{
	// Print out the received message.
	printer.print("[" + username + "]: " + message);
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
		srvListener = new ServerRepliesListener(&srvConnection, &printer, this);
		srvListener->start();

		// Start listening to peer messages (Even though there are currently no peers).
		peerListener = new PeerMessageListener(this);
		peerListener->start();
	}
	else
	{
		printer.print("Connection failed!");
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
	// Close all UDP sockets.
	peerListener->stop();

	// Stop listening for server responses
	srvListener->stop();

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

	// Open a socket to the other user
	peerListener->openSocket(otherUsername, otherUserAddr);

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

	string currentUsername;
	string currentUserAddress = srvConnection.receiveMessage();

	// Get all the users' connection data ,and add another UDP socket for each
	// While we haven't received the DONE_SENDING_ROOM_PARTICIPANTS code
	while (currentUserAddress.compare(DONE_SENDING_ROOM_PARTICIPANTS) != 0)
	{
		// Receive the username
		currentUsername = srvConnection.receiveMessage();

		// Open a socket to the other user
		peerListener->openSocket(currentUsername, currentUserAddress);

		// TODO: Remove this
		printer.print("Connected to " + currentUsername + "( " + currentUserAddress + ").");

		// Get the next user address
		currentUserAddress = srvConnection.receiveMessage();
	}

	printer.print("All connections established. You have joined the room.");
}

void ClientController::notifySomeoneJoinedRoom()
{
	// Receive the relevant data from the server.
	string joiningUsername = srvConnection.receiveMessage();
	string joiningUserAddr = srvConnection.receiveMessage();

	// Open another socket to the joining user
	peerListener->openSocket(joiningUsername, joiningUserAddr);

	printer.print(joiningUsername + " has joined the room.");
}

void ClientController::notifySomeoneLeftRoom()
{
	// Receive the relevant data from the server.
	string exitingUsername = srvConnection.receiveMessage();

	// Close the socket to the leaving user
	peerListener->closeSocket(exitingUsername);

	printer.print(exitingUsername + " has left the room.");
}

void ClientController::notifyExitRoom()
{
	// Close all UDP sockets
	peerListener->closeAllSockets();

	printer.print("You have left the room.");
}

void ClientController::notifySessionClosed()
{
	// Receive the relevant data from the server.
	string otherUsername = srvConnection.receiveMessage();

	// Close the session socket
	peerListener->closeSocket(otherUsername);

	printer.print("Session with " + otherUsername + " has ended.");
}

void ClientController::notifyRoomClosedByOwner()
{
	// Receive the relevant data from the server.
	string roomName = srvConnection.receiveMessage();

	// Close all UDP sockets
	peerListener->closeAllSockets();

	printer.print("ChatRoom '" + roomName + "' closed by its owner.");
}

void ClientController::notifyRoomClosedSuccess()
{
	printer.print("Closing the room..");
}

void ClientController::notifyServerShuttingDown()
{
	printer.print("Server is shutting down, Disconnecting..");

	// Disconnect and stop listening to the server.
	notifyDisconnected();
}

ServerRepliesObserver::~ServerRepliesObserver() {}
SessionMessageObserver::~SessionMessageObserver() {}

