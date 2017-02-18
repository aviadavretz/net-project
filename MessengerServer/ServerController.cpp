/*
 * ServerController.cpp
 *
 *  Created on: Feb 18, 2017
 *      Author: user
 */

#include "ServerController.h"

ServerController::ServerController() : peersAcceptor(ServerPeersAcceptor(this))
{
}

void ServerController::startServer()
{
	peersAcceptor.start();
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
	cout << "New peer accepted from address : " << peerSocket->fromAddr() << " !" << endl;
}

void ServerController::notifyMessageReceived(TCPSocket* peerSocket, string message)
{
	cout << "Message received : " << message << endl;
}

void ServerController::stopServer()
{
	peersAcceptor.stop();
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


