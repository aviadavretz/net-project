/*
 * ServerPeersListener.cpp
 *
 *  Created on: Feb 18, 2017
 *      Author: user
 */

#include "ServerPeersListener.h"
#include <algorithm>

ServerPeersListener::ServerPeersListener(PeerMessagesObserver* observer)
{
	this->observer = observer;
	shouldContinue = true;
}

void ServerPeersListener::run()
{
	while (shouldContinue)
	{
		MTCPListener listener;
		listener.add(peers);

		int timeout = 3;
		TCPSocket* readyPeer = listener.listen(timeout);

		// No message received for the past given timeout seconds
		if (readyPeer == NULL)
		{
			continue;
		}

		int commandCode = readCommand(readyPeer);

		routeCommand(commandCode, readyPeer);
	}
}

int ServerPeersListener::readCommand(TCPSocket* socket)
{
	int command = 0;

	// Receive command (the size should be as stated in the protocol)
	int bytesReceived = socket->recv((char*)&command, EXPECTED_COMMAND_BYTES_SIZE);

	return ntohl(command);
}

void ServerPeersListener::routeCommand(int command, TCPSocket* peer)
{
	// TODO: TCPProtocol
	int OPEN_CHAT_ROOM = 11;
	int JOIN_CHAT_ROOM = 14;
	int CLOSE_SESSION_OR_EXIT_ROOM = 15;

	if (command == LOGIN)
	{
		routeLoginCommand(peer);
	}
	else if (command == REGISTER)
	{
		routeRegisterCommand(peer);
	}
	else if (command == DISCONNECT)
	{
		routeDisconnectCommand(peer);
	}
	else if (command == OPEN_CHAT_ROOM)
	{
		routeOpenChatRoomCommand(peer);
	}
	else if (command == JOIN_CHAT_ROOM)
	{
		routeJoinChatRoomCommand(peer);
	}
	else if (command == CLOSE_SESSION_OR_EXIT_ROOM)
	{
		routeCloseSessionOrExitRoom(peer);
	}
}

void ServerPeersListener::routeCloseSessionOrExitRoom(TCPSocket* peer)
{
	observer->notifyCloseSessionOrExitRoomRequest(peer);
}

void ServerPeersListener::routeJoinChatRoomCommand(TCPSocket* peer)
{
	// Message = 1 argument = room name
	string roomName = readMessage(peer);

	observer->notifyJoinChatRoomRequest(peer, roomName);
}

void ServerPeersListener::routeOpenChatRoomCommand(TCPSocket* peer)
{
	// Message = 1 argument = room name
	string roomName = readMessage(peer);

	observer->notifyOpenChatRoomRequest(peer, roomName);
}

void ServerPeersListener::routeLoginCommand(TCPSocket* peer)
{
	string message = readMessage(peer);
	pair<string, string> usernamePassword = getUsernameAndPasswordFromMessage(message);

	observer->notifyLoginRequest(peer, usernamePassword.first, usernamePassword.second);
}

void ServerPeersListener::routeDisconnectCommand(TCPSocket* peer)
{
	observer->notifyDisconnectRequest(peer);
}

void ServerPeersListener::routeRegisterCommand(TCPSocket* peer)
{
	string message = readMessage(peer);
	pair<string, string> usernamePassword = getUsernameAndPasswordFromMessage(message);

	observer->notifyRegistrationRequest(peer, usernamePassword.first, usernamePassword.second);
}

string ServerPeersListener::readMessage(TCPSocket* socket)
{
	char messageContent[256];
	int messageLength;

	// Receiving message length
	socket->recv((char*)&messageLength, EXPECTED_MESSAGE_LENGTH_INDICATOR_BYTES_SIZE);

	messageLength = ntohl(messageLength);

	// Receiving the message content
	socket->recv(messageContent, messageLength);
	messageContent[messageLength] = '\0';

	return string(messageContent);
}

void ServerPeersListener::stop()
{
	shouldContinue = false;
}

void ServerPeersListener::addPeer(TCPSocket* peer)
{
	peers.push_back(peer);
}

void ServerPeersListener::removePeer(TCPSocket* peer)
{
	// TODO: Implement this without #include <algorithm>?
	vector<TCPSocket*>::iterator position = std::find(peers.begin(), peers.end(), peer);

	 // end() means the element was not found
	if (position != peers.end())
	{
		peers.erase(position);
	}
}

pair<string, string> ServerPeersListener::getUsernameAndPasswordFromMessage(string message)
{
	string::size_type delimiterIndex = message.find(USERNAME_PASSWORD_DELIMITER, 0);

	if (delimiterIndex != string::npos)
	{
		string username = message.substr(0, delimiterIndex);
		string password = message.substr(delimiterIndex + 1, message.length());

		return make_pair(username, password);
	}

	return make_pair("","");
}

