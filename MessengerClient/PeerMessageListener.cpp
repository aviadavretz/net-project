/*
 * PeerMessageListener.cpp
 *
 *  Created on: Mar 5, 2017
 *      Author: user
 */

#include "PeerMessageListener.h"

void PeerMessageListener::run()
{
	while (shouldContinue)
	{
		MUDPListener listener;
		map<string, UDPSocket*>::iterator iter;

		// TODO: Think of a better way to do this.. maybe add & remove them outside
		for (iter = sockets.begin(); iter != sockets.end(); iter++)
		{
			UDPSocket* currSocket = (*iter).second;
			listener.add(currSocket);
		}

		int timeout = 3;
		UDPSocket* readyPeer = listener.listen(timeout);

		// No message received for the past given timeout seconds
		if (readyPeer == NULL)
		{
			continue;
		}

		// Get the message & username
		string message = readMessage(readyPeer);
		string username = getUsernameBySocket(readyPeer);

		observer->notifyMessageReceived(username, message);
	}
}

string PeerMessageListener::readMessage(UDPSocket* socket)
{
	char messageContent[256];
	int messageLength;

	// Receiving message length
	socket->recv((char*)&messageLength, EXPECTED_MESSAGE_LENGTH_INDICATOR_BYTES_SIZE);

	messageLength = ntohl(messageLength);

	// Receiving the message content
	socket->recv(messageContent, messageLength);
	messageContent[messageLength] = '\0';

	return string(messageContent);
}

string PeerMessageListener::getUsernameBySocket(UDPSocket* socketToFind)
{
	map<string, UDPSocket*>::iterator iter;

	// Go over each value and return the sockets key.
	for (iter = sockets.begin(); iter != sockets.end(); iter++)
	{
		UDPSocket* currSocket = (*iter).second;

		if (socketToFind == currSocket)
		{
			return (*iter).first;
		}
	}

	return "N/A";
}

void PeerMessageListener::openSocket(string otherUsername, string address)
{
	// Create a new socket
	UDPSocket* newSocket = new UDPSocket(address, SESSION_PORT);

	// Add the socket to the map of sockets.
	sockets[otherUsername] = newSocket;
}

void PeerMessageListener::closeSocket(string otherUsername)
{
	UDPSocket* socketToClose = sockets[otherUsername];

	// Close the socket
	socketToClose->close();

	// Remove the socket from the map of sockets.
	sockets[otherUsername] = NULL;
}

/**
 * This function should only be called when disconnecting
 */
void PeerMessageListener::stop()
{
	shouldContinue = false;
	closeAllSockets();
}

void PeerMessageListener::closeAllSockets()
{
	map<string, UDPSocket*>::iterator iter;

	for (iter = sockets.begin(); iter != sockets.end(); iter++)
	{
		UDPSocket* currSocket = (*iter).second;

		// Close the socket
		currSocket->close();
	}

	sockets.clear();
}

PeerMessageListener::PeerMessageListener(SessionMessageObserver* observer)
{
	this->observer = observer;

	shouldContinue = true;
}

PeerMessageListener::~PeerMessageListener() {}

