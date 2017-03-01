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
	for (vector<ChatRoom*>::iterator iterator = chatRooms.begin(); iterator != chatRooms.end(); iterator++)
	{
		string currentRoomName = (*iterator)->getName();

		if (currentRoomName.compare(name) == 0)
		{
			return *iterator;
		}
	}

	return NULL;
}

void ServerController::notifyNewPeerAccepted(TCPSocket* peerSocket)
{
	peersListener.addPeer(peerSocket);

	printer.printNewPeerAccepted(peerSocket->fromAddr());

	// Send back confirmation to the client
	peersMessageSender.sendConnectSuccess(peerSocket);
}

void ServerController::notifyOpenSessionRequest(TCPSocket* peerSocket, string otherUserName)
{
	// Make sure the peer is logged in
	if (!isPeerLoggedIn(peerSocket))
	{
		peersMessageSender.sendNotLoggedIn(peerSocket);
		printer.print(peerSocket->fromAddr() + " tried to open a session, but is not logged in.");
	}
	else
	{
		User* requestingUser = getUserByPeer(peerSocket);

		// Make sure the requesting user is not currently in a session or room
		if (isBusyUser(requestingUser))
		{
			peersMessageSender.sendAlreadyBusy(peerSocket);
			printer.print(requestingUser->getUsername() + " wants to create a Session, but is currently in a Session or ChatRoom.");
		}
		else
		{
			// Check if user exists and is logged in
			if (isUserConnected(otherUserName))
			{
				User* otherUser = getConnectedUserByUsername(otherUserName);

				// Make sure the other user is not busy
				if (isBusyUser(otherUser))
				{
					peersMessageSender.sendOtherUserBusy(peerSocket);
					printer.print(requestingUser->getUsername() + " wants to create a Session with " + otherUserName +
								  ", but " + otherUserName + " is busy.");
				}
				else
				{
					// Other user is not busy. Create the session
					Session* session = new Session(requestingUser, otherUser);

					sessions.push_back(session);

					peersMessageSender.sendOpenSessionSuccess(peerSocket);
					printer.print(requestingUser->getUsername() + " has created a Session with " + otherUserName);

					// TODO: Need to send the socket info to the users?
				}
			}
			else
			{
				// User not found
				peersMessageSender.sendUserNotFound(peerSocket);
				printer.print(requestingUser->getUsername() + " tried to open a Session with " + otherUserName +
						      ", but there is no logged in user named " + otherUserName);
			}
		}
	}
}

void ServerController::notifyCloseChatRoomRequest(TCPSocket* peerSocket, string roomName)
{
	// Make sure the peer is logged in
	if (!isPeerLoggedIn(peerSocket))
	{
		peersMessageSender.sendNotLoggedIn(peerSocket);
		printer.print(peerSocket->fromAddr() + " tried to close a room, but is not logged in.");
	}
	else
	{
		User* requestingUser = getUserByPeer(peerSocket);

		// Check if a room by the requested name exists.
		if (getChatRoomByName(roomName) == NULL)
		{
			peersMessageSender.sendRoomDoesntExist(peerSocket);
			printer.print(requestingUser->getUsername() + " tried to close a room named '" +
						  roomName + "', but a room with that name doesn't exist.");
		}
		else
		{
			ChatRoom* roomToClose = getChatRoomByName(roomName);

			// TODO: Bug: This always says it's the owner!!
			// TODO: Only username? or User* object
			if (roomToClose->getOwner()->getUsername().compare(requestingUser->getUsername()) != 0)
			{
				peersMessageSender.sendNotRoomOwner(peerSocket);
				printer.print(requestingUser->getUsername() + " tried to close a room named '" +
							roomName + "', but the owner is " + roomToClose->getOwner()->getUsername());
			}
			else
			{
				// TODO: Implement this without #include <algorithm>?
				vector<ChatRoom*>::iterator position = std::find(chatRooms.begin(), chatRooms.end(), roomToClose);

				// end() means the element was not found
				if (position != chatRooms.end())
				{
					chatRooms.erase(position);

					// TODO: Need to disconnect all users from it?

					// TODO: Need to send notifications to all clients inside the room

					peersMessageSender.sendCloseRoomSuccess(peerSocket);
					printer.print("ChatRoom '" + roomName + "' has been closed by " +
						      	  requestingUser->getUsername() + " (" + peerSocket->fromAddr() + ").");
				}
			}
		}
	}
}

void ServerController::notifyCloseSessionOrExitRoomRequest(TCPSocket* peerSocket)
{
	// Make sure the peer is logged in
	if (!isPeerLoggedIn(peerSocket))
	{
		peersMessageSender.sendNotLoggedIn(peerSocket);
		printer.print(peerSocket->fromAddr() + " tried to join a room, but is not logged in.");
	}
	else
	{
		User* requestingUser = getUserByPeer(peerSocket);

		// Room
		if (isUserInChatRoom(requestingUser))
		{
			// Remove the user from the room he is inside
			ChatRoom* userRoom = getRoomByUser(requestingUser);
			userRoom->removeParticipant(requestingUser);

			peersMessageSender.sendExitRoomSuccess(peerSocket);
			printer.print(requestingUser->getUsername() + " has left ChatRoom '" + userRoom->getName() + "'.");
		}
		// Session
		else if (isUserInSession(requestingUser))
		{
			// Remove the user from the session he is participating in
			Session* userSession = getSessionByUser(requestingUser);

			// TODO: Close the session?
			// TODO: Implement this without #include <algorithm>?
			vector<Session*>::iterator position = std::find(sessions.begin(), sessions.end(), userSession);

			 // end() means the element was not found
			if (position != sessions.end())
			{
				sessions.erase(position);

				peersMessageSender.sendCloseSessionSuccess(peerSocket);
				string otherUserName = userSession->getSecondUser()->getUsername();

				// If the requesting user is the second user in the session
				if (otherUserName.compare(requestingUser->getUsername()) == 0)
				{
					otherUserName = userSession->getFirstUser()->getUsername();
				}

				printer.print(requestingUser->getUsername() +
							  " has closed the Session with " + otherUserName + ".");
			}
		}
		else
		{
			peersMessageSender.sendNotInSessionOrRoom(peerSocket);
			printer.print(requestingUser->getUsername() +
					      " tried to close session or exit room, but does not participate in either.");
		}
	}
}

void ServerController::notifyJoinChatRoomRequest(TCPSocket* peerSocket, string roomName)
{
	// Make sure the peer is logged in
	if (!isPeerLoggedIn(peerSocket))
	{
		peersMessageSender.sendNotLoggedIn(peerSocket);
		printer.print(peerSocket->fromAddr() + " tried to join a room, but is not logged in.");
	}
	else
	{
		User* requestingUser = getUserByPeer(peerSocket);

		// Make sure the requesting user is not in a session or chat-room
		if (isBusyUser(requestingUser))
		{
			peersMessageSender.sendAlreadyBusy(peerSocket);
			printer.print(requestingUser->getUsername() + " tried to join a room, but is already in a room or session.");
		}
		else
		{
			ChatRoom* room = getChatRoomByName(roomName);

			// Make sure a room with the requested name exists.
			if (room == NULL)
			{
				peersMessageSender.sendRoomDoesntExist(peerSocket);
				printer.print(requestingUser->getUsername() + " tried to join a room named '" +
						  	  roomName + "', but it doesnt exist.");
			}
			else
			{
				room->addParticipant(requestingUser);

				peersMessageSender.sendJoinRoomSuccess(peerSocket);
				printer.print(requestingUser->getUsername() + " (" + peerSocket->fromAddr() +
					      	  ") joined ChatRoom '" + roomName + "'");
			}
		}
	}
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
		if (getChatRoomByName(roomName) != NULL)
		{
			peersMessageSender.sendRoomNameExists(peerSocket);
			printer.print(requestingUser->getUsername() + " tried to open a room named '" +
						  roomName + "', but a room with that name already exists.");
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
		User* user = getUserByPeer(peerSocket);

		if (isUserInChatRoom(user))
		{
			// Remove the user from the room he is inside
			ChatRoom* usersRoom = getRoomByUser(user);
			usersRoom->removeParticipant(user);
		}

		notification = user->getUsername() + " (" +peerSocket->fromAddr() + ") has disconnected.";

		// Remove the user from the vector of connected users.
		connectedUsers.erase(peerSocket);
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

bool ServerController::isUserConnected(string username)
{
	return getConnectedUserByUsername(username) != NULL;
}

User* ServerController::getConnectedUserByUsername(string username)
{
 	for (map<TCPSocket*, User*>::iterator iterator = connectedUsers.begin(); iterator != connectedUsers.end(); iterator++)
	{
 		User* currentUser = (*iterator).second;

		if (currentUser->getUsername().compare(username) == 0)
		{
			// Return the User object
			return currentUser;
		}
	}

 	return NULL;
}



bool ServerController::isUserInSession(User* user)
{
	return getSessionByUser(user) != NULL;
}

// TODO: Maybe create a map<user*, Session*> for this?
Session* ServerController::getSessionByUser(User* user)
{
 	for (vector<Session*>::iterator iterator = sessions.begin(); iterator != sessions.end(); iterator++)
	{
 		User* firstUser = (*iterator)->getFirstUser();
 		User* secondUser = (*iterator)->getSecondUser();

		// TODO: Compare whole User* objects?
		if ((firstUser->getUsername().compare(user->getUsername()) == 0) ||
			(secondUser->getUsername().compare(user->getUsername()) == 0))
		{
			// Return the Session object
			return (*iterator);
		}
	}

 	return NULL;
}

bool ServerController::isUserInChatRoom(User* user)
{
 	return getRoomByUser(user) != NULL;
}

// TODO: Maybe create a map<user*, room*> for this?
ChatRoom* ServerController::getRoomByUser(User* user)
{
 	for (vector<ChatRoom*>::iterator iterator = chatRooms.begin(); iterator != chatRooms.end(); iterator++)
	{
		vector<User*> currentRoomUsers = (*iterator)->getParticipatingUsers();

		for (vector<User*>::iterator iterator2 = currentRoomUsers.begin(); iterator2 != currentRoomUsers.end(); iterator2++)
		{
			// TODO: Compare whole User* objects?
			if ((*iterator2)->getUsername().compare(user->getUsername()) == 0)
			{
				// Return the ChatRoom object
				return (*iterator);
			}
		}
	}

 	return NULL;
}

bool ServerController::isBusyUser(User* user)
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


