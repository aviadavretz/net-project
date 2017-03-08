/*
 * ServerPeersMessageSender.cpp
 *
 *  Created on: Feb 19, 2017
 *      Author: user
 */

#include "ServerPeersMessageSender.h"

void ServerPeersMessageSender::sendCode(TCPSocket* peer, int code)
{
	int message = htonl(code);
	peer->send((char*)&message, EXPECTED_COMMAND_BYTES_SIZE);
}

void ServerPeersMessageSender::sendMessage(TCPSocket* peer, string message)
{
	int messageLength = htonl(message.length());
	peer->send((char*)&messageLength, EXPECTED_MESSAGE_LENGTH_INDICATOR_BYTES_SIZE);
	peer->send(message);
}

void ServerPeersMessageSender::sendStringList(TCPSocket* peer, int code, vector<string> strings)
{
	// Send the code first
	sendCode(peer, code);

	// Send the list length
    std::stringstream stringsSizeMessage;
    stringsSizeMessage << strings.size();
	sendMessage(peer, stringsSizeMessage.str());

	// Send the list itself
	for (vector<string>::iterator iterator = strings.begin(); iterator != strings.end(); iterator++)
	{
		sendMessage(peer, *iterator);
	}
}

void ServerPeersMessageSender::sendRoomWasClosed(TCPSocket* peer, string roomName)
{
	// Send the code
	sendCode(peer, ROOM_CLOSED_BY_OWNER);

	// Send the roomName
	sendMessage(peer, roomName);
}

void ServerPeersMessageSender::sendSomeoneJoinedRoom(TCPSocket* peer)
{
	// Send the code
	sendCode(peer, SOMEONE_JOINED_CHAT_ROOM);
}

void ServerPeersMessageSender::sendSomeoneLeftRoom(TCPSocket* peer, string leavingUsername)
{
	// Send the code
	sendCode(peer, SOMEONE_LEFT_CHAT_ROOM);

	// Send the leaving username
	sendMessage(peer, leavingUsername);
}

void ServerPeersMessageSender::sendStatusFree(TCPSocket* peer)
{
	sendCode(peer, STATUS_FREE);
}

void ServerPeersMessageSender::sendStatusInASession(TCPSocket* peer)
{
	sendCode(peer, STATUS_IN_A_SESSION);
}

void ServerPeersMessageSender::sendStatusInARoom(TCPSocket* peer)
{
	sendCode(peer, STATUS_IN_A_ROOM);
}

void ServerPeersMessageSender::sendUserAlreadyLoggedIn(TCPSocket* peer)
{
	sendCode(peer, USER_ALREADY_LOGGED_IN);
}

void ServerPeersMessageSender::sendSessionWithSelf(TCPSocket* peer)
{
	sendCode(peer, SESSION_WITH_SELF);
}

void ServerPeersMessageSender::sendUserNotFound(TCPSocket* peer)
{
	sendCode(peer, USER_NOT_FOUND);
}

void ServerPeersMessageSender::sendOtherUserBusy(TCPSocket* peer)
{
	sendCode(peer, OTHER_USER_BUSY);
}

void ServerPeersMessageSender::sendOpenSessionSuccess(TCPSocket* peer)
{
	sendCode(peer, SESSION_ESTABLISHED);
}

void ServerPeersMessageSender::sendNotRoomOwner(TCPSocket* peer)
{
	sendCode(peer, NOT_ROOM_OWNER);
}

void ServerPeersMessageSender::sendCloseRoomSuccess(TCPSocket* peer)
{
	sendCode(peer, CLOSE_ROOM_SUCCESS);
}

void ServerPeersMessageSender::sendExitRoomSuccess(TCPSocket* peer)
{
	sendCode(peer, EXIT_ROOM_SUCCESS);
}

void ServerPeersMessageSender::sendCloseSessionSuccess(TCPSocket* peer, string otherUsername)
{
	// Send the code
	sendCode(peer, CLOSE_SESSION_SUCCESS);

	// Send the other users name
	sendMessage(peer, otherUsername);
}

void ServerPeersMessageSender::sendNotInSessionOrRoom(TCPSocket* peer)
{
	sendCode(peer, NOT_IN_SESSION_OR_ROOM);
}

void ServerPeersMessageSender::sendNotLoggedIn(TCPSocket* peer)
{
	sendCode(peer, NOT_LOGGED_IN);
}

void ServerPeersMessageSender::sendRoomDoesntExist(TCPSocket* peer)
{
	sendCode(peer, ROOM_DOES_NOT_EXIST);
}

void ServerPeersMessageSender::sendJoinRoomSuccess(TCPSocket* peer)
{
	sendCode(peer, JOIN_ROOM_SUCCESS);
}

void ServerPeersMessageSender::sendAlreadyInRequestedRoom(TCPSocket* peer)
{
	sendCode(peer, ALREADY_IN_REQUESTED_ROOM);
}

void ServerPeersMessageSender::sendRoomNameExists(TCPSocket* peer)
{
	sendCode(peer, ROOM_NAME_EXISTS);
}

void ServerPeersMessageSender::sendOpenRoomSuccess(TCPSocket* peer, string roomName)
{
	// Send the code
	sendCode(peer, OPEN_CHAT_ROOM_SUCCESS);

	// Send the room name
	sendMessage(peer, roomName);
}

void ServerPeersMessageSender::sendClientAlreadyLoggedIn(TCPSocket* peer)
{
	sendCode(peer, CLIENT_ALREADY_LOGGED_IN);
}

void ServerPeersMessageSender::sendBadUsernamePassword(TCPSocket* peer)
{
	sendCode(peer, BAD_USERNAME_PASSWORD);
}

void ServerPeersMessageSender::sendLoginSuccessful(TCPSocket* peer)
{
	sendCode(peer, LOGIN_SUCCEEDED);
}

void ServerPeersMessageSender::sendRegisterFailed(TCPSocket* peer)
{
	sendCode(peer, REGISTER_FAILURE);
}

void ServerPeersMessageSender::sendRegisterSuccessful(TCPSocket* peer)
{
	sendCode(peer, REGISTER_SUCCEEDED);
}

void ServerPeersMessageSender::sendUsernameExists(TCPSocket* peer)
{
	sendCode(peer, USERNAME_EXISTS);
}

void ServerPeersMessageSender::sendConnectSuccess(TCPSocket* peer)
{
	sendCode(peer, CONNECT_SUCCESS);
}

void ServerPeersMessageSender::sendDisconnectSuccess(TCPSocket* peer)
{
	sendCode(peer, DISCONNECT_SUCCESS);
}

void ServerPeersMessageSender::sendServerShuttingDown(TCPSocket* peer)
{
	sendCode(peer, SERVER_SHUTTING_DOWN);
}

void ServerPeersMessageSender::sendAllRegisterdUsers(TCPSocket* peer, vector<string> usernames)
{
	sendStringList(peer, GET_REGISTERED_USERS, usernames);
}

void ServerPeersMessageSender::sendAllConnectedUsers(TCPSocket* peer, vector<string> usernames)
{
	sendStringList(peer, GET_CONNECTED_USERS, usernames);
}

void ServerPeersMessageSender::sendAllRooms(TCPSocket* peer, vector<string> roomNames)
{
	sendStringList(peer, GET_CHAT_ROOMS, roomNames);
}

void ServerPeersMessageSender::sendAllUsersInRoom(TCPSocket* peer, vector<string> usernames)
{
	sendStringList(peer, GET_USERS_IN_CHAT_ROOM, usernames);
}

void ServerPeersMessageSender::sendEstablishedSessionCommunicationDetails(TCPSocket* initiatingPeer, User* initiatingUser, int initiatingListenPort,
																          TCPSocket* receivingPeer, User* receivingUser, int receivingListenPort)
{
	// Notify both peers that a session has been established
	sendOpenSessionSuccess(initiatingPeer);
	sendOpenSessionSuccess(receivingPeer);

	// Send both each others connection data
	sendConnectionData(initiatingPeer, initiatingUser->getUsername(), initiatingListenPort,
					   receivingPeer, receivingUser->getUsername(), receivingListenPort);
}

// TODO: Maybe use sendCode instead?
#include <sstream>

void ServerPeersMessageSender::sendConnectionData(TCPSocket* first, string firstUsername, int firstListenPort,
												  TCPSocket* second, string secondUsername, int secondListenPort)
{
	// Convert the ports to strings
	ostringstream port1;
	ostringstream port2;
	port1 << firstListenPort;
	port2 << secondListenPort;

	// Send the second username, address & port to the first user
	sendMessage(first, secondUsername);
	sendMessage(first, second->fromAddr());
	sendMessage(first, port2.str());

	// Send the first username, address & port to the second user
	sendMessage(second, firstUsername);
	sendMessage(second, first->fromAddr());
	sendMessage(second, port1.str());
}


