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

void ServerPeersMessageSender::sendAlreadyInARoom(TCPSocket* peer)
{
	// TODO: Put this in TCPProtocol
	int ALREADY_IN_A_ROOM = 462;
	sendCode(peer, ALREADY_IN_A_ROOM);
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

void ServerPeersMessageSender::sendAlreadyLoggedIn(TCPSocket* peer)
{
	sendCode(peer, ALREADY_LOGGED_IN);
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



