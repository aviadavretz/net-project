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
	vector<TCPSocket*> allConnectedSockets = peersListener.getAllConnectedSockets();

	// Notify every connected socket that the server is shutting down (Not just logged-in, but also just connected sockets).
	for (vector<TCPSocket*>::iterator iterator = allConnectedSockets.begin(); iterator != allConnectedSockets.end(); iterator++)
	{
		// Notify the current user that the server is shutting down
		peersMessageSender.sendServerShuttingDown((*iterator));
	}

	// Stop listening and accepting incoming connections
	peersAcceptor.stop();
	peersAcceptor.closeSockets();

	peersListener.stop();
}

string ServerController::getOtherUsernameBySession(Session* session, string knownUsername)
{
	string otherUsername = session->getSecondUser()->getUsername();

	// If the known user is the second user in the session
	if (otherUsername.compare(knownUsername) == 0)
	{
		// Return the first
		return session->getFirstUser()->getUsername();
	}

	return otherUsername;
}

void ServerController::closeExistingSessions(TCPSocket* peerSocket, User* requestingUser)
{
	// Check if the requesting user is currently in a session
	if (isUserInSession(requestingUser))
	{
		printer.print(requestingUser->getUsername() + " wants to create a Session, but is currently in a Session.");

		Session* oldSession = getSessionByUser(requestingUser);

		// Close the old session
		closeSession(oldSession);

		// Get the other username & socket
		string otherSessionUsername = getOtherUsernameBySession(oldSession, requestingUser->getUsername());
		TCPSocket* otherSocket = getPeerSocketByUsername(otherSessionUsername);

		// Notify the users that the session has ended.
		peersMessageSender.sendCloseSessionSuccess(peerSocket, otherSessionUsername);
		peersMessageSender.sendCloseSessionSuccess(otherSocket, requestingUser->getUsername());

		printer.print("Session between " + requestingUser->getUsername() + " and " + otherSessionUsername + " closed.");
	}
	// Check if the requesting user is currently in a room
	else if (isUserInChatRoom(requestingUser))
	{
		// TODO: Implement this!!!
		printer.print(requestingUser->getUsername() + " wants to create a Session, but is currently in a ChatRoom.");
	}
}

vector<string> ServerController::getAllRegisteredUsersName()
{
	return userCredentialsManager.getAllRegisteredUsersName();
}

vector<string> ServerController::getAllConnectedUsersName()
{
	vector<string> users;
	map<TCPSocket*,User*>::iterator iterator;

	for (iterator = loggedInUsers.begin(); iterator != loggedInUsers.end(); iterator++)
	{
		users.push_back(iterator->second->getUsername());
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

void ServerController::notifyListeningPort(TCPSocket* peerSocket, int listeningPort)
{
	// Save the users port.
	peerListeningPorts[peerSocket] = listeningPort;

	printer.printListenPort(peerSocket->fromAddr(), listeningPort);
}

void ServerController::notifyStatusRequest(TCPSocket* peerSocket)
{
	// Make sure the peer is logged in
	if (!isPeerLoggedIn(peerSocket))
	{
		peersMessageSender.sendNotLoggedIn(peerSocket);
		printer.print(peerSocket->fromAddr() + " requested status: Not logged in.");
	}
	else
	{
		User* requestingUser = getUserByPeer(peerSocket);

		// Check if the user is in a room
		if (isUserInChatRoom(requestingUser))
		{
			// The user is in a room
			peersMessageSender.sendStatusInARoom(peerSocket);

			// Get the room in which the user is
			ChatRoom* usersRoom = getRoomByUser(requestingUser);
			string roomName = usersRoom->getName();

			// Send the roomName to the user
			peersMessageSender.sendMessage(peerSocket, roomName);

			printer.print(requestingUser->getUsername() + " requested status: In a room (" + roomName + ").");
		}
		// Check if the user is in a session
		else if (isUserInSession(requestingUser))
		{
			// The user is in a session
			peersMessageSender.sendStatusInASession(peerSocket);

			// Get the session in which the user is
			Session* userSession = getSessionByUser(requestingUser);

			// Get the other username
			string otherUserName = getOtherUsernameBySession(userSession, requestingUser->getUsername());

			// Send the otherUserName to the user
			peersMessageSender.sendMessage(peerSocket, otherUserName);

			printer.print(requestingUser->getUsername() + " requested status: In a session with " + otherUserName + ".");
		}
		else
		{
			// The user is logged in, but not in a session or room
			peersMessageSender.sendStatusFree(peerSocket);
			printer.print(requestingUser->getUsername() + " requested status: Not in a room or session.");
		}

		// Send the username to the user.
		peersMessageSender.sendMessage(peerSocket, requestingUser->getUsername());
	}
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

		// Make sure the other user is not the requesting user.
		if (otherUserName.compare(requestingUser->getUsername()) == 0)
		{
			peersMessageSender.sendSessionWithSelf(peerSocket);
			printer.print(requestingUser->getUsername() + " tried to create a Session with himself.");
		}
		else
		{
//			// Check if the requesting user is not currently in a session or room
//			if (isBusyUser(requestingUser))
//			{
//				peersMessageSender.sendAlreadyBusy(peerSocket);
//				printer.print(requestingUser->getUsername() + " wants to create a Session, but is currently in a Session or ChatRoom.");
//			}
//			else
//			{
				// Check if user exists and is logged in
				if (isUserLoggedIn(otherUserName))
				{
					TCPSocket* otherPeer = getPeerSocketByUsername(otherUserName);
					User* otherUser = getUserByPeer(otherPeer);

					// Make sure the other user is not busy
					if (isBusyUser(otherUser))
					{
						peersMessageSender.sendOtherUserBusy(peerSocket);
						printer.print(requestingUser->getUsername() + " wants to create a Session with " + otherUserName +
									  ", but " + otherUserName + " is busy.");
					}
					else
					{
						// Close the existing sessions of the requesting user.
						closeExistingSessions(peerSocket, requestingUser);

						// Get the listening port of each participant
						int requestingUserPort = peerListeningPorts[peerSocket];
						int otherUserPort = peerListeningPorts[otherPeer];

						// Other user is not busy. Create the session
						Session* session = new Session(requestingUser, otherUser);

						sessions.push_back(session);

						peersMessageSender.sendEstablishedSessionCommunicationDetails(
								peerSocket, requestingUser, requestingUserPort,
								otherPeer, otherUser, otherUserPort);

						printer.print(requestingUser->getUsername() + " has created a Session with " + otherUserName);
					}
				}
				else
				{
					// User not found
					peersMessageSender.sendUserNotFound(peerSocket);
					printer.print(requestingUser->getUsername() + " tried to open a Session with " + otherUserName +
								  ", but there is no logged in user named " + otherUserName);
				}
//			}
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

			// Check if the requesting user is the owner of the room
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

					// Notify the requesting user that the room is being closed.
					peersMessageSender.sendCloseRoomSuccess(peerSocket);

					vector<User*> roomUsers = roomToClose->getParticipatingUsers();
					bool ownerIsInside = false;

					// Notify every user in the room.
					for (vector<User*>::iterator iter = roomUsers.begin(); iter != roomUsers.end(); iter++)
					{
						string currentUsername = (*iter)->getUsername();

						// Check if the owner (requesting user) is in the room
						if (currentUsername.compare(requestingUser->getUsername()) == 0)
						{
							ownerIsInside = true;
						}

						// Get the current relevant socket
						TCPSocket* currentUserSocket = getPeerSocketByUsername(currentUsername);

						// Notify the user that the room closed
						peersMessageSender.sendRoomWasClosed(currentUserSocket, roomName);
					}

					// If the owner wasn't in the room when it closed, notify him as well.
					if (!ownerIsInside)
					{
						peersMessageSender.sendRoomWasClosed(peerSocket, roomName);
					}

					printer.print("ChatRoom '" + roomName + "' has been closed by " +
						      	  requestingUser->getUsername() + " (" + peerSocket->fromAddr() + ").");
				}
			}
		}
	}
}

bool ServerController::closeSession(Session* session)
{
	// TODO: Implement this without #include <algorithm>?
	vector<Session*>::iterator position = std::find(sessions.begin(), sessions.end(), session);

	 // end() means the element was not found
	if (position != sessions.end())
	{
		sessions.erase(position);
		return true;
	}

	return false;
}

void ServerController::notifyCloseSessionOrExitRoomRequest(TCPSocket* peerSocket)
{
	// Make sure the peer is logged in
	if (!isPeerLoggedIn(peerSocket))
	{
		peersMessageSender.sendNotLoggedIn(peerSocket);
		printer.print(peerSocket->fromAddr() + " tried to close session / exit a room, but is not logged in.");
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

			vector<User*> roomUsers = userRoom->getParticipatingUsers();

			// Notify every user in the room.
			for (vector<User*>::iterator iter = roomUsers.begin(); iter != roomUsers.end(); iter++)
			{
				// Get the current relevant socket
				TCPSocket* currentUserSocket = getPeerSocketByUsername((*iter)->getUsername());

				// Notify the user that someone has left.
				peersMessageSender.sendSomeoneLeftRoom(currentUserSocket, requestingUser->getUsername());
			}

			// Notify the user he has left the room
			peersMessageSender.sendExitRoomSuccess(peerSocket);

			printer.print(requestingUser->getUsername() + " has left ChatRoom '" + userRoom->getName() + "'.");
		}
		// Session
		else if (isUserInSession(requestingUser))
		{
			// Close the session the user is in
			Session* userSession = getSessionByUser(requestingUser);

			// Delete the session
			bool success = closeSession(userSession);

			if (success)
			{
				// Get the other username
				string otherUsername = getOtherUsernameBySession(userSession, requestingUser->getUsername());

				// Get the other socket
				TCPSocket* otherSocket = getPeerSocketByUsername(otherUsername);

				// Notify both users that the session has ended.
				peersMessageSender.sendCloseSessionSuccess(peerSocket, otherUsername);
				peersMessageSender.sendCloseSessionSuccess(otherSocket, requestingUser->getUsername());

				printer.print(requestingUser->getUsername() +
							  " has closed the Session with " + otherUsername + ".");
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
			// TODO: Leave the current session/room and create a new one?
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
				// Notify the user he has joined the room.
				peersMessageSender.sendJoinRoomSuccess(peerSocket);
				vector<User*> roomUsers = room->getParticipatingUsers();
				int requestingUserPort = peerListeningPorts[peerSocket];
				int otherUserPort;

				// Send the relevant data to every user.
				for (vector<User*>::iterator iter = roomUsers.begin(); iter != roomUsers.end(); iter++)
				{
					string currentUsername = (*iter)->getUsername();

					// Get the current relevant socket
					TCPSocket* currentUserSocket = getPeerSocketByUsername(currentUsername);

					// Get the listening port of the other participant
					int otherUserPort = peerListeningPorts[currentUserSocket];

					// Notify the old user that someone has joined.
					peersMessageSender.sendSomeoneJoinedRoom(currentUserSocket);

					// Send both the joining user and the old user each-other's information
					peersMessageSender.sendConnectionData(peerSocket, requestingUser->getUsername(), requestingUserPort,
														  currentUserSocket, currentUsername, otherUserPort);
				}

				// Notify the user that he has all the room users data.
				peersMessageSender.sendMessage(peerSocket, DONE_SENDING_ROOM_PARTICIPANTS);

				// Add the requesting user to the room.
				room->addParticipant(requestingUser);

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

			peersMessageSender.sendOpenRoomSuccess(peerSocket, roomName);
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
		User* requestingUser = getUserByPeer(peerSocket);

		// Check if user is busy
		if (isUserInChatRoom(requestingUser))
		{
			// Remove the user from the room he is inside
			ChatRoom* usersRoom = getRoomByUser(requestingUser);
			usersRoom->removeParticipant(requestingUser);

			// Notify all other room users that the requesting user has left
			vector<User*> roomUsers = usersRoom->getParticipatingUsers();

			// Notify every user in the room.
			for (vector<User*>::iterator iter = roomUsers.begin(); iter != roomUsers.end(); iter++)
			{
				// Get the current relevant socket
				TCPSocket* currentUserSocket = getPeerSocketByUsername((*iter)->getUsername());

				// Notify the user that someone has left.
				peersMessageSender.sendSomeoneLeftRoom(currentUserSocket, requestingUser->getUsername());
			}
		}
		else if (isUserInSession(requestingUser))
		{
			// Close the session the user is in
			Session* userSession = getSessionByUser(requestingUser);
			closeSession(userSession);

			// Get the other other username
			string otherUsername = getOtherUsernameBySession(userSession, requestingUser->getUsername());

			// Get the other socket
			TCPSocket* otherSocket = getPeerSocketByUsername(otherUsername);

			// Notify the other user that the session has ended.
			peersMessageSender.sendCloseSessionSuccess(otherSocket, requestingUser->getUsername());
		}

		notification = requestingUser->getUsername() + " (" +peerSocket->fromAddr() + ") has disconnected.";

		// Remove the user from the vector of connected users.
		loggedInUsers.erase(peerSocket);
	}
	else
	{
		notification = peerSocket->fromAddr() + " has disconnected.";
	}

	// Stop listening to this peer.
	peersListener.removePeer(peerSocket);

	// Delete the users listening port
	peerListeningPorts.erase(peerSocket);

	printer.print(notification);

	// Send back confirmation to the client
	peersMessageSender.sendDisconnectSuccess(peerSocket);
}

void ServerController::notifyLoginRequest(TCPSocket* peerSocket, string username, string password)
{
	string address = peerSocket->fromAddr();

	// Make sure the peer is not already logged in
	if (isPeerLoggedIn(peerSocket))
	{
		peersMessageSender.sendClientAlreadyLoggedIn(peerSocket);
		printer.print(address+" tried to login but is already logged in.");
	}
	else
	{
		// Make sure the user we are trying to login to is not already logged in
		if (isUserLoggedIn(username))
		{
			peersMessageSender.sendUserAlreadyLoggedIn(peerSocket);
			printer.print(username+" ("+address+") tried to login, but is already logged in.");
		}
		else
		{
			// Validate the username & password
			if (!userCredentialsManager.validateUserCredentials(username, password))
			{
				peersMessageSender.sendBadUsernamePassword(peerSocket);
				printer.print(address+" tried to login with a wrong username/password: " + username + ", " + password);
			}
			else
			{
				// User & PSW are correct.
				User* user = new User(username);
				loggedInUsers[peerSocket] = user;

				peersMessageSender.sendLoginSuccessful(peerSocket);
				printer.printLoginSuccessful(username, address);
			}
		}
	}
}

void ServerController::notifyRegistrationRequest(TCPSocket* peerSocket, string username, string password)
{
	if (isPeerLoggedIn(peerSocket))
	{
		peersMessageSender.sendClientAlreadyLoggedIn(peerSocket);
		printer.print(username+" tried to register, but is already logged in to another user.");
	}
	else
	{
		if (userCredentialsManager.doesUsernameExist(username))
		{
			peersMessageSender.sendUsernameExists(peerSocket);
			printer.print(username+" tried to register, but username exists.");
		}
		else
		{
			if (userCredentialsManager.signUp(username, password))
			{
				peersMessageSender.sendRegisterSuccessful(peerSocket);

				printer.print(username+" has registered.");

				// Login
				notifyLoginRequest(peerSocket, username, password);
			}
			else
			{
				peersMessageSender.sendRegisterFailed(peerSocket);
				printer.print(username+" tried to register but failed.");
			}
		}
	}
}

void ServerController::notifyListAllUsersRequest(TCPSocket* peerSocket)
{
	peersMessageSender.sendAllRegisterdUsers(peerSocket, getAllRegisteredUsersName());
	printer.print(peerSocket->fromAddr() + " has requested a list of all registered users.");
}

void ServerController::notifyListAllConnectedUsersRequest(TCPSocket* peerSocket)
{
	peersMessageSender.sendAllConnectedUsers(peerSocket, getAllConnectedUsersName());
	printer.print(peerSocket->fromAddr() + " has requested a list of all connected users.");
}

void ServerController::notifyListAllRoomsRequest(TCPSocket* peerSocket)
{
	vector<string> roomNames;

	// Build a list containing the room names
	for (vector<ChatRoom*>::iterator iterator = chatRooms.begin(); iterator != chatRooms.end(); iterator++)
	{
		roomNames.push_back((*iterator)->getName());
	}

	peersMessageSender.sendAllRooms(peerSocket, roomNames);

	printer.print(peerSocket->fromAddr() + " has requested a list of all rooms.");
}

void ServerController::notifyListAllUsersInRoomRequest(TCPSocket* peerSocket, string roomName)
{
	ChatRoom* referencedRoom = getChatRoomByName(roomName);

	// Make sure the room exists
	if (referencedRoom == NULL)
	{
		peersMessageSender.sendRoomDoesntExist(peerSocket);
		printer.print(peerSocket->fromAddr() + " has requested a list of all users in the room '" +
					  roomName + "', but there is no room with that name.");
	}
	else
	{
		// Get the User* objects who are in that room
		vector<User*> usersInRoom = referencedRoom->getParticipatingUsers();

		vector<string> userNames;

		// Build a list with the usernames instead of the User* objects
		for (vector<User*>::iterator iterator = usersInRoom.begin(); iterator != usersInRoom.end(); iterator++)
		{
			userNames.push_back((*iterator)->getUsername());
		}

		peersMessageSender.sendAllUsersInRoom(peerSocket, userNames);

		printer.print(peerSocket->fromAddr() + " has requested a list of all users in the room '" + roomName + "'.");
	}
}

bool ServerController::isUserLoggedIn(string username)
{
	return getLoggedInUserByUsername(username) != NULL;
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
	return loggedInUsers[peer];
}

bool ServerController::isPeerLoggedIn(TCPSocket* peer)
{
	return getUserByPeer(peer) != NULL;
}

TCPSocket* ServerController::getPeerSocketByUsername(string username)
{
 	for (map<TCPSocket*, User*>::iterator iterator = loggedInUsers.begin(); iterator != loggedInUsers.end(); iterator++)
	{
 		User* currentUser = (*iterator).second;

 		// TODO: Somewhere we insert the socket after it connects and the User* remains NULL.
 		// TODO: It's ok though, because that way, when we shutdown server we notify all connected (and just logged-in) users.
 		// In case the map holds the socket as the key, but no value.
 		if (currentUser == NULL) { continue; }

 		// Compare the usernames
		if (username.compare(currentUser->getUsername()) == 0)
		{
			// Return the User object
			return iterator->first;
		}
	}

 	return NULL;
}

User* ServerController::getLoggedInUserByUsername(string username)
{
	TCPSocket* peerSocket = getPeerSocketByUsername(username);

	if (peerSocket != NULL)
	{
		return getUserByPeer(peerSocket);
	}

	return NULL;
}

NewPeerAcceptedObserver::~NewPeerAcceptedObserver(){}

PeerMessagesObserver::~PeerMessagesObserver(){}

