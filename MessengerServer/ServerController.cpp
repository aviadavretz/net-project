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

	printer.printNewPeerAccepted(peerSocket->fromAddr());

	// Send back confirmation to the client
	peersMessageSender.sendConnectSuccess(peerSocket);
}

void ServerController::notifyOpenChatRoomRequest(TCPSocket* peerSocket, string roomName)
{
	if (!isPeerLoggedIn(peerSocket))
	{
		peersMessageSender.sendNotLoggedIn(peerSocket);
		printer.print(peerSocket->fromAddr() + " tried to open a room, but is not logged in.");
	}
	else
	{
		User* requestingUser = getUserByPeer(peerSocket);

		// Check if a room by the requested name already exists.
		// TODO: This "!= NULL" thing doesnt work..
		if (getChatRoomByName(roomName) != NULL)
		{
			peersMessageSender.sendRoomNameExists(peerSocket);
			printer.print(requestingUser->getUsername() + " tried to open a room named '" +
						  roomName + ", but a room with that name already exists.");
		}
		else
		{

			ChatRoom* newRoom = new ChatRoom(roomName, requestingUser);

			chatRooms.push_back(newRoom);

			peersMessageSender.sendOpenRoomSuccess(peerSocket);
			printer.print("ChatRoom '" + roomName + "' has been created by " +
				      	  requestingUser->getUsername() + " (" + peerSocket->fromAddr() + ").");
		}
	}
}

void ServerController::notifyDisconnectRequest(TCPSocket* peerSocket)
{
	string notification;
	if (isPeerLoggedIn(peerSocket))
	{
		string username = getUserByPeer(peerSocket)->getUsername();

		notification = username + " (" +peerSocket->fromAddr() + ") has disconnected.";

	}
	else
	{
		notification = peerSocket->fromAddr() + " has disconnected.";
	}

	peersListener.removePeer(peerSocket);

	printer.print(notification);

	// Send back confirmation to the client
	peersMessageSender.sendDisconnectSuccess(peerSocket);
	peerSocket->close();
}

void ServerController::notifyLoginRequest(TCPSocket* peerSocket, string username, string password)
{
	string address = peerSocket->fromAddr();

	if (isPeerLoggedIn(peerSocket))
	{
		peersMessageSender.sendAlreadyLoggedIn(peerSocket);
		printer.print(address.append(" tried to login but is already logged in."));
	}
	else
	{
		if (!userCredentialsManager.validateUserCredentials(username, password))
		{
			peersMessageSender.sendBadUsernamePassword(peerSocket);
			printer.print(username.append(" (").append(address).append(") tried to login with a wrong username/password."));
		}
		else
		{
			User* user = new User(username);
			connectedUsers[peerSocket] = user;

			peersMessageSender.sendLoginSuccessful(peerSocket);
			printer.printLoginSuccessful(username, address);
		}
	}
}

void ServerController::notifyRegistrationRequest(TCPSocket* peerSocket, string username, string password)
{
	if (isPeerLoggedIn(peerSocket))
	{
		peersMessageSender.sendAlreadyLoggedIn(peerSocket);
		printer.print(username.append(" tried to register, but is already logged in to another user."));
	}
	else
	{
		if (userCredentialsManager.doesUsernameExist(username))
		{
			peersMessageSender.sendUsernameExists(peerSocket);
			printer.print(username.append(" tried to register, but username exists."));
		}
		else
		{
			if (userCredentialsManager.signUp(username, password))
			{
				peersMessageSender.sendRegisterSuccessful(peerSocket);
				printer.print(username.append(" has registered."));
			}
			else
			{
				peersMessageSender.sendRegisterFailed(peerSocket);
				printer.print(username.append(" tried to register but failed."));
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


