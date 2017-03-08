/*
 * ConnectionToServerManager.cpp
 *
 *  Created on: Mar 2, 2017
 *      Author: user
 */

#include "ConnectionToServerManager.h"

string ConnectionToServerManager::receiveMessage()
{
	char messageContent[256];
	int messageLength;

	// Receiving message length
	socketToServer->recv((char*)&messageLength, EXPECTED_MESSAGE_LENGTH_INDICATOR_BYTES_SIZE);

	messageLength = ntohl(messageLength);

	// Receiving the message content
	socketToServer->recv(messageContent, messageLength);
	messageContent[messageLength] = '\0';

	// Convert the char* to string
	return string(messageContent);
}

int ConnectionToServerManager::receiveIntMessage()
{
	char messageContent[256];
	int messageLength;

	// Receiving message length
	socketToServer->recv((char*)&messageLength, EXPECTED_MESSAGE_LENGTH_INDICATOR_BYTES_SIZE);

	messageLength = ntohl(messageLength);

	// Receiving the message content
	socketToServer->recv(messageContent, messageLength);
	messageContent[messageLength] = '\0';

	// Convert the char* to int
	return atoi(messageContent);
}

string ConnectionToServerManager::getAddr()
{
	if (socketToServer != NULL)
	{
		return socketToServer->fromAddr();
	}

	return "N/A";
}

vector<string> ConnectionToServerManager::receiveMessages(int messagesNumber)
{
	vector<string> messages;

	// Receive messages from the server and adding them to the vector, according to the messages number given
	for (int i = 0; i < messagesNumber; i++)
	{
		messages.push_back(receiveMessage());
	}

	return messages;
}

int ConnectionToServerManager::receiveReplyCode()
{
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
	delete socketToServer;
}
