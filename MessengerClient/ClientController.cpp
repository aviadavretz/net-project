
/*
 * ClientController.cpp
 *
 *  Created on: Feb 27, 2017
 *      Author: user
 */

#include "ClientController.h"

ClientController::ClientController() : connected(false), loggedIn(false), username("N/A"), srvListener(NULL), peerListener(NULL) {}

bool ClientController::isConnected()
{
	return connected;
}

bool ClientController::isInSessionOrRoom()
{
	return !peerListener->arePeersEmpty();
}

bool ClientController::isLoggedIn()
{
	return loggedIn;
}

string ClientController::getLoggedInUsername()
{
	return username;
}

void ClientController::sendMessage(string sendingUsername, string message)
{
	// Append the username to the message
	string messageToSend = ">[" + sendingUsername + "] " + message;

	// Send the message to all peers
	peerListener->sendMessage(messageToSend);
}

void ClientController::notifyMessageReceived(string message)
{
	// Print out the received message.
	printer.print(message);
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

		// Start listening to incoming messages from peers
		startPeerListening();

		// Send the listening port to the server.
		int listeningPort = peerListener->getListeningPort();

		// Convert the int port to a string value
		ostringstream ss;
		ss << listeningPort;

		sendCommandToServer(NOTIFY_LISTENING_PORT, ss.str());
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

	// Save the username for later (If login fails, we won't use it anyway).
	this->username = username;
}

void ClientController::registerUser(string username, string password)
{
	// Send register command to the server with username and password
	sendCommandToServer(REGISTER, username + " " + password);

	// Save the username for later, because the server will login. (If register fails, we won't use it anyway).
	this->username = username;
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

void ClientController::notifyLogInSuccess()
{
	loggedIn = true;
	printer.print("Login successful as " + username + ".");
}

void ClientController::notifyDisconnected()
{
	// Stop listening to peers messages
	stopPeerListening();

	// Stop listening for server responses
	srvListener->stop();

	// Close the socket
	srvConnection.closeSocket();
	username = "N/A";
	loggedIn = false;
	connected = false;

	printer.print("Disconnected from server.");
}

void ClientController::notifySessionEstablished()
{
	// Receive the relevant data from the server.
	string otherUsername = srvConnection.receiveMessage();
	string otherUserAddr = srvConnection.receiveMessage();
	int otherUserListeningPort = srvConnection.receiveIntMessage();

	// Open a socket to the other user
	peerListener->addPeer(otherUsername, otherUserAddr, otherUserListeningPort);
	printer.printConnectionEstablished(otherUsername, otherUserAddr, otherUserListeningPort);
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

	string currentUsername = srvConnection.receiveMessage();
	string currentUserAddress;
	int otherUserListeningPort;

	// Get all the users' connection data ,and add another UDP socket for each
	// While we haven't received the DONE_SENDING_ROOM_PARTICIPANTS code
	while (currentUsername.compare(DONE_SENDING_ROOM_PARTICIPANTS) != 0)
	{
		// Receive the address & port
		currentUserAddress = srvConnection.receiveMessage();
		otherUserListeningPort = srvConnection.receiveIntMessage();

		// Open a socket to the other user
		peerListener->addPeer(currentUsername, currentUserAddress, otherUserListeningPort);

		// Get the next username
		currentUsername = srvConnection.receiveMessage();
	}

	printer.print("All connections established. You have joined the room.");
}

void ClientController::notifySomeoneJoinedRoom()
{
	// Receive the relevant data from the server.
	string joiningUsername = srvConnection.receiveMessage();
	string joiningUserAddr = srvConnection.receiveMessage();
	int otherUserListeningPort = srvConnection.receiveIntMessage();

	// Open another socket to the joining user
	peerListener->addPeer(joiningUsername, joiningUserAddr, otherUserListeningPort);

	printer.print(joiningUsername + " has joined the room.");
}

void ClientController::notifySomeoneLeftRoom()
{
	// Receive the relevant data from the server.
	string exitingUsername = srvConnection.receiveMessage();

	// Close the socket to the leaving user
	peerListener->removePeerByUsername(exitingUsername);

	printer.print(exitingUsername + " has left the room.");
}

void ClientController::notifyExitRoom()
{
	// Remove all peers from listener
	peerListener->removeAllPeers();

	printer.print("You have left the room.");
}

void ClientController::notifySessionClosed()
{
	// Receive the relevant data from the server.
	string otherUsername = srvConnection.receiveMessage();

	// Remove peer from listener
	peerListener->removePeerByUsername(otherUsername);

	printer.print("Session with " + otherUsername + " has ended.");
}

void ClientController::notifyRoomClosedByOwner()
{
	// Receive the relevant data from the server.
	string roomName = srvConnection.receiveMessage();

	// Remove all peers from listener
	peerListener->removeAllPeers();

	printer.print("ChatRoom '" + roomName + "' closed by its owner.");
}

void ClientController::notifyYouClosedRoom()
{
	// Receive the relevant data from the server.
	string roomName = srvConnection.receiveMessage();

	printer.print("You have closed ChatRoom '" + roomName + "'.");
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

void ClientController::startPeerListening()
{
	peerListener = new PeerMessageListener(this);
	peerListener->start();
}

void ClientController::stopPeerListening()
{
	if (peerListener != NULL)
	{
		// Close the session socket
		peerListener->stop();
		delete peerListener;
	}
}

ServerRepliesObserver::~ServerRepliesObserver() {}
SessionMessageObserver::~SessionMessageObserver() {}

