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
	pthread_mutex_init(&peersMutex, NULL);
	shouldContinue = true;
}

vector<TCPSocket*> ServerPeersListener::getAllConnectedSockets()
{
	// Make sure peers are not modified while accessing it
	pthread_mutex_lock(&peersMutex);

	vector<TCPSocket*> peers = this->peers;

	// We finished accessing peers so we can unlock
	pthread_mutex_unlock(&peersMutex);

	return peers;

}

void ServerPeersListener::run()
{
	while (shouldContinue)
	{
		// Create an MTCPListener and add the connected sockets to it
		MTCPListener listener;
		listener.add(getAllConnectedSockets());

		// Listen to incoming messages from connected peers, with a timeout.
		int timeout = 3;
		TCPSocket* readyPeer = listener.listen(timeout);

		// No message received for the past given timeout seconds
		if (readyPeer == NULL)
		{
			continue;
		}

		// Read the incoming command
		int commandCode = readCommand(readyPeer);

		// Route, process & execute the user command
		routeCommand(commandCode, readyPeer);
	}
}

int ServerPeersListener::readCommand(TCPSocket* socket)
{
	int commandCode = 0;

	// Receive command (the size should be as stated in the protocol)
	int bytesReceived = socket->recv((char*)&commandCode, EXPECTED_COMMAND_BYTES_SIZE);

	return ntohl(commandCode);
}

void ServerPeersListener::routeCommand(int commandCode, TCPSocket* peer)
{
	switch (commandCode)
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
		case (NOTIFY_LISTENING_PORT):
		{
			routeNotifyListeningPort(peer);
			break;
		}
		default:
		{
			break;
		}
	}
}

void ServerPeersListener::routeNotifyListeningPort(TCPSocket* peer)
{
	// Message = 1 argument = user's port
	int listeningPort = readIntMessage(peer);

	observer->notifyListeningPort(peer, listeningPort);
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
	// Extract the username & password from the message
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

int ServerPeersListener::readIntMessage(TCPSocket* socket)
{
	char messageContent[256];
	int messageLength;

	// Receiving message length
	socket->recv((char*)&messageLength, EXPECTED_MESSAGE_LENGTH_INDICATOR_BYTES_SIZE);

	messageLength = ntohl(messageLength);

	// Receiving the message content
	socket->recv(messageContent, messageLength);
	messageContent[messageLength] = '\0';

	// Convert char* to int
	return atoi(messageContent);
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

	// Convert char* to string
	return string(messageContent);
}

void ServerPeersListener::stop()
{
	shouldContinue = false;

	vector<TCPSocket*> peers = getAllConnectedSockets();

	// Delete all sockets
	for (vector<TCPSocket*>::iterator iterator = peers.begin(); iterator != peers.end(); iterator++)
	{
		TCPSocket* currentSocket = (*iterator);

		// Close & delete this socket.
		currentSocket->close();
		delete currentSocket;
	}
}

void ServerPeersListener::addPeer(TCPSocket* peer)
{
	// Make sure peers are not modified while appending
	pthread_mutex_lock(&peersMutex);

	// Add the peer
	peers.push_back(peer);

	// Appending done so we can unlock
	pthread_mutex_unlock(&peersMutex);
}

void ServerPeersListener::removePeer(TCPSocket* peer)
{
	// Make sure peers are not modified while erasing
	pthread_mutex_lock(&peersMutex);

	// Find the position of the requested element
	vector<TCPSocket*>::iterator position = std::find(peers.begin(), peers.end(), peer);

	 // end() means the element was not found
	if (position != peers.end())
	{
		peers.erase(position);
	}

	// We finished erasing so we can unlock
	pthread_mutex_unlock(&peersMutex);
}

pair<string, string> ServerPeersListener::getUsernameAndPasswordFromMessage(string message)
{
	// Get the index of the delimiter
	string::size_type delimiterIndex = message.find(USERNAME_PASSWORD_DELIMITER, 0);

	// Make sure it exists
	if (delimiterIndex != string::npos)
	{
		// Cut the string to get username and password
		string username = message.substr(0, delimiterIndex);
		string password = message.substr(delimiterIndex + 1, message.length());

		// Create a pair<string, string>
		return make_pair(username, password);
	}

	return make_pair("","");
}

