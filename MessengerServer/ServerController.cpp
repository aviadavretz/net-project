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

void ServerController::stopServer()
{
	peersAcceptor.stop();
	peersListener.stop();
}

vector<string> ServerController::getAllRegisteredUsersName()
{
	return userCredentialsManager.getAllRegisteredUsersName();
}

vector<User*> ServerController::getAllConnectedUsers()
{
	vector<User*> users;
	map<TCPSocket*,User*>::iterator iterator;

	for (iterator = connectedUsers.begin(); iterator != connectedUsers.end(); iterator++)
	{
		users.push_back(iterator->second);
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
		cout << "already logged in" << endl;
		// TODO : Return "already logged in" code
	}
	else
	{
		if (!userCredentialsManager.validateUserCredentials(username, password))
		{
			cout << "bad username / password" << endl;
			// TODO : Return "bad username / password" code
		}
		else
		{
			User* user = new User(username);
			connectedUsers[peerSocket] = user;

			cout << "login success" << endl;
			// TODO : Return "login success" code
		}
	}
}

void ServerController::notifyRegistrationRequest(TCPSocket* peerSocket, string username, string password)
{
	if (isPeerLoggedIn(peerSocket))
	{
		cout << "cant register when logged in" << endl;
		// TODO : Return "cant register when logged in" code
	}
	else
	{
		if (userCredentialsManager.doesUsernameExist(username))
		{
			cout << "username already exists" << endl;
			// TODO : return "username already exists" code
		}
		else
		{
			if (userCredentialsManager.signUp(username, password))
			{
				cout << "register success" << endl;
				// TODO : return "register success" code
			}
			else
			{
				cout << "register failed" << endl;
				// TODO : return "register failed" code
			}
		}
	}
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


