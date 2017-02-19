/*
 * ServerController.cpp
 *
 *  Created on: Feb 18, 2017
 *      Author: user
 */

#include "ServerController.h"

ServerController::ServerController() : peersAcceptor(ServerPeersAcceptor(this)), peersListener(ServerPeersListener(this))
{
}

void ServerController::startServer()
{
	peersAcceptor.start();
	peersListener.start();
}

vector<string> ServerController::getAllRegisteredUsersName()
{
	return userCredentialsManager.getAllRegisteredUsersName();
}

vector<User*> ServerController::getAllConnectedUsers()
{
	vector<User*> users;

	for(auto const& imap: connectedUsers)
	{
		users.push_back(imap.second);
	}

	return users;
}

vector<Session*> ServerController::getAllSessions()
{
	return sessions;
}

vector<ChatRoom*> ServerController::getAllChatRooms()
{
	return chatRooms;
}

ChatRoom* ServerController::getChatRoomByName(string name)
{
	return NULL;
}

void ServerController::notifyNewPeerAccepted(TCPSocket* peerSocket)
{
	peersListener.addPeer(peerSocket);
}

void ServerController::notifyLoginRequest(TCPSocket* peerSocket, string username, string password)
{
	if (isPeerLoggedIn(peerSocket))
	{
		// TODO : Return "already logged in" message
	}
	else
	{
		bool loginSuccessed = userCredentialsManager.validateUserCredentials(username, password);

		if (loginSuccessed)
		{
			// TODO : Return "bad username / password" message
		}
		else
		{
			User* user = new User(username);
			connectedUsers[peerSocket] = user;

			// TODO : Return "login success" message
		}
	}
}

void ServerController::notifyRegistrationRequest(TCPSocket* peerSocket, string username, string password)
{
	if (isPeerLoggedIn(peerSocket))
	{
		// TODO : Return "cant register when logged in" message
	}
	else
	{
		bool registrationSuccessed = false;

		if (userCredentialsManager.validateUserCredentials(username, password))
		{
			// TODO :
		}
		else
		{
			registrationSuccessed = userCredentialsManager.signUp(username, password);
		}
	}
}

void ServerController::stopServer()
{
	peersAcceptor.stop();
	peersListener.stop();
}

bool isUserInSession(User* user)
{
	return true;
}

bool isUserInChatRoom(User* user)
{
	return true;
}

bool isBusyUser(User* user)
{
	return isUserInChatRoom(user) || isUserInSession(user);
}

User* ServerController::getUserByPeer(TCPSocket* peer)
{
	return connectedUsers[peer];
}

bool ServerController::isPeerLoggedIn(TCPSocket* peer)
{
	return getUserByPeer(peer) != NULL;
}

NewPeerAcceptedObserver::~NewPeerAcceptedObserver(){}

PeerMessagesObserver::~PeerMessagesObserver(){}


