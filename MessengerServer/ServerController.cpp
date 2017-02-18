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
	return loginManager.getAllRegisteredUsersName();
}

vector<User*> ServerController::getAllConnectedUsers()
{
	return connectedUsers;
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
	bool loginSuccessed = loginManager.validateUserCredentials(username, password);
	cout << "Login attempt : " << loginSuccessed << endl;

	// TODO : Implement further login actions
}

void ServerController::notifyRegistrationRequest(TCPSocket* peerSocket, string username, string password)
{
	bool registrationSuccessed = false;

	if (!loginManager.validateUserCredentials(username, password))
	{
		registrationSuccessed = loginManager.signUp(username, password);
	}

	cout << "Registration attempt : " << registrationSuccessed << endl;

	// TODO : Implement further register actions
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

NewPeerAcceptedObserver::~NewPeerAcceptedObserver(){}

PeerMessagesObserver::~PeerMessagesObserver(){}


