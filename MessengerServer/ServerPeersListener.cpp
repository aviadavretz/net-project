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
	const int OPEN_CHAT_ROOM = 11;
	const int JOIN_CHAT_ROOM = 14;
	const int CLOSE_SESSION_OR_EXIT_ROOM = 15;
	const int CLOSE_ROOM = 16;
	const int GET_STATUS = 17;
	const int OPEN_SESSION_WITH_PEER = 2;

	switch (command)
	{
		case (LOGIN):
		{
			routeLoginCommand(peer);
			break;
		}
		case (REGISTER):
		{
			routeRegisterCommand(peer);
			break;
		}
		case (DISCONNECT):
		{
			routeDisconnectCommand(peer);
			break;
		}
		case (OPEN_CHAT_ROOM):
		{
			routeOpenChatRoomCommand(peer);
			break;
		}
		case (JOIN_CHAT_ROOM):
		{
			routeJoinChatRoomCommand(peer);
			break;
		}
		case (CLOSE_SESSION_OR_EXIT_ROOM):
		{
			routeCloseSessionOrExitRoomCommand(peer);
			break;
		}
		case (CLOSE_ROOM):
		{
			routeCloseChatRoomCommand(peer);
			break;
		}
		case (OPEN_SESSION_WITH_PEER):
		{
			routeOpenSessionCommand(peer);
			break;
		}
		case (GET_REGISTERED_USERS):
		{
			routeGetAllRegisteredUsers(peer);
			break;
		}
		case (GET_CONNECTED_USERS):
		{
			routeGetAllConnectedUsers(peer);
			break;
		}
		case (GET_CHAT_ROOMS):
		{
			routeGetAllRooms(peer);
			break;
		}
		case (GET_USERS_IN_CHAT_ROOM):
		{
			routeGetUsersInRoom(peer);
			break;
		}
		case (GET_STATUS):
		{
			routeStatusRequest(peer);
			break;
		}
		default:
		{
			break;
		}
	}
}

void ServerPeersListener::routeStatusRequest(TCPSocket* peer)
{
	observer->notifyStatusRequest(peer);
}

void ServerPeersListener::routeOpenSessionCommand(TCPSocket* peer)
{
	// Message = 1 argument = username to start session with
	string otherUserName = readMessage(peer);

	observer->notifyOpenSessionRequest(peer, otherUserName);
}

void ServerPeersListener::routeCloseChatRoomCommand(TCPSocket* peer)
{
	// Message = 1 argument = room name
	string roomName = readMessage(peer);

	observer->notifyCloseChatRoomRequest(peer, roomName);
}

void ServerPeersListener::routeCloseSessionOrExitRoomCommand(TCPSocket* peer)
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

void ServerPeersListener::routeGetAllRegisteredUsers(TCPSocket* peer)
{
	observer->notifyListAllUsersRequest(peer);
}

void ServerPeersListener::routeGetAllConnectedUsers(TCPSocket* peer)
{
	observer->notifyListAllConnectedUsersRequest(peer);
}

void ServerPeersListener::routeGetAllRooms(TCPSocket* peer)
{
	observer->notifyListAllRoomsRequest(peer);
}

void ServerPeersListener::routeGetUsersInRoom(TCPSocket* peer)
{
	// Message = 1 argument = room name
	string roomName = readMessage(peer);

	observer->notifyListAllUsersInRoomRequest(peer, roomName);
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

