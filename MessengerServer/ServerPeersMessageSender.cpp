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



