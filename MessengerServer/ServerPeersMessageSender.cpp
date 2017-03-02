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

void ServerPeersMessageSender::sendStatusFree(TCPSocket* peer)
{
	// TODO: Put this in TCPProtocol
	int STATUS_FREE = 540;
	sendCode(peer, STATUS_FREE);
}

void ServerPeersMessageSender::sendStatusInASession(TCPSocket* peer)
{
	// TODO: Put this in TCPProtocol
	int STATUS_IN_A_SESSION = 542;
	sendCode(peer, STATUS_IN_A_SESSION);
}

void ServerPeersMessageSender::sendStatusInARoom(TCPSocket* peer)
{
	// TODO: Put this in TCPProtocol
	int STATUS_IN_A_ROOM = 541;
	sendCode(peer, STATUS_IN_A_ROOM);
}

void ServerPeersMessageSender::sendUserAlreadyLoggedIn(TCPSocket* peer)
{
	// TODO: Put this in TCPProtocol
	int USER_ALREADY_LOGGED_IN = 207;
	sendCode(peer, USER_ALREADY_LOGGED_IN);
}

void ServerPeersMessageSender::sendSessionWithSelf(TCPSocket* peer)
{
	// TODO: Put this in TCPProtocol
	int SESSION_WITH_SELF = 524;
	sendCode(peer, SESSION_WITH_SELF);
}

void ServerPeersMessageSender::sendUserNotFound(TCPSocket* peer)
{
	// TODO: Put this in TCPProtocol
	int USER_NOT_FOUND = 522;
	sendCode(peer, USER_NOT_FOUND);
}

void ServerPeersMessageSender::sendOtherUserBusy(TCPSocket* peer)
{
	// TODO: Put this in TCPProtocol
	int OTHER_USER_BUSY = 523;
	sendCode(peer, OTHER_USER_BUSY);
}

void ServerPeersMessageSender::sendOpenSessionSuccess(TCPSocket* peer)
{
	sendCode(peer, SESSION_ESTABLISHED);
}

void ServerPeersMessageSender::sendNotRoomOwner(TCPSocket* peer)
{
	// TODO: Put this in TCPProtocol
	int NOT_ROOM_OWNER = 501;
	sendCode(peer, NOT_ROOM_OWNER);
}

void ServerPeersMessageSender::sendCloseRoomSuccess(TCPSocket* peer)
{
	// TODO: Get this from TCPProtocol
	int CLOSE_ROOM_SUCCESS = 500;
	sendCode(peer, CLOSE_ROOM_SUCCESS);
}

void ServerPeersMessageSender::sendExitRoomSuccess(TCPSocket* peer)
{
	// TODO: Put this in TCPProtocol
	int EXIT_ROOM_SUCCESS = 480;
	sendCode(peer, EXIT_ROOM_SUCCESS);
}

void ServerPeersMessageSender::sendCloseSessionSuccess(TCPSocket* peer)
{
	// TODO: Put this in TCPProtocol
	int CLOSE_SESSION_SUCCESS = 490;
	sendCode(peer, CLOSE_SESSION_SUCCESS);
}

void ServerPeersMessageSender::sendNotInSessionOrRoom(TCPSocket* peer)
{
	// TODO: Put this in TCPProtocol
	int NOT_IN_SESSION_OR_ROOM = 481;
	sendCode(peer, NOT_IN_SESSION_OR_ROOM);
}

void ServerPeersMessageSender::sendNotLoggedIn(TCPSocket* peer)
{
	// TODO: Put this in TCPProtocol
	int NOT_LOGGED_IN = 206;
	sendCode(peer, NOT_LOGGED_IN);
}

void ServerPeersMessageSender::sendRoomDoesntExist(TCPSocket* peer)
{
	// TODO: Put this in TCPProtocol
	int ROOM_DOESNT_EXISTS = 461;
	sendCode(peer, ROOM_DOESNT_EXISTS);
}

void ServerPeersMessageSender::sendJoinRoomSuccess(TCPSocket* peer)
{
	// TODO: Put this in TCPProtocol
	int JOIN_ROOM_SUCCESS = 460;
	sendCode(peer, JOIN_ROOM_SUCCESS);
}

void ServerPeersMessageSender::sendAlreadyBusy(TCPSocket* peer)
{
	// TODO: Put this in TCPProtocol
	int ALREADY_BUSY = 462;
	sendCode(peer, ALREADY_BUSY);
}

void ServerPeersMessageSender::sendRoomNameExists(TCPSocket* peer)
{
	// TODO: Put this in TCPProtocol
	int ROOM_NAME_EXISTS = 441;
	sendCode(peer, ROOM_NAME_EXISTS);
}

void ServerPeersMessageSender::sendOpenRoomSuccess(TCPSocket* peer)
{
	// TODO: Put this in TCPProtocol
	int OPEN_CHAT_ROOM_SUCCESS = 440;
	sendCode(peer, OPEN_CHAT_ROOM_SUCCESS);
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
	// TODO: Put this in TCPProtocol
	int CONNECT_SUCCESS = 420;
	sendCode(peer, CONNECT_SUCCESS);
}

void ServerPeersMessageSender::sendDisconnectSuccess(TCPSocket* peer)
{
	// TODO: Put this in TCPProtocol
	int DISCONNECT_SUCCESS = 421;
	sendCode(peer, DISCONNECT_SUCCESS);
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
