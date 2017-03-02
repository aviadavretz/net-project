/*
 * ConnectionToServerManager.cpp
 *
 *  Created on: Mar 2, 2017
 *      Author: user
 */

#include "ConnectionToServerManager.h"

ConnectionToServerManager::ConnectionToServerManager() {}
ConnectionToServerManager::~ConnectionToServerManager() {}

int ConnectionToServerManager::receiveReplyCode()
{
	// TODO: TCPProtocol
	int EXPECTED_COMMAND_BYTES_SIZE = 4;

	// Receive reply (the size should be as stated in the protocol)
	int reply = 0;
	int bytesReceived = socketToServer->recv((char*)&reply, EXPECTED_COMMAND_BYTES_SIZE);
	int returnedCode = ntohl(reply);

	return returnedCode;
}

void ConnectionToServerManager::sendCommandCode(int commandCode)
{
	// Send the command-code
	int commandLength = htonl(commandCode);
	socketToServer->send((char*)&commandLength,4);
}

void ConnectionToServerManager::sendArgs(string message)
{
	// Send the arguments as a single message
	int messageLength = htonl(message.length());

	// Send the message length first
	socketToServer->send((char*)&messageLength, 4);

	// Send the message itself
	socketToServer->send(message);
}

void ConnectionToServerManager::openSocket(string address, int port)
{
	socketToServer = new TCPSocket(address, port);
}

void ConnectionToServerManager::closeSocket()
{
	socketToServer->close();
	socketToServer = NULL;
}
