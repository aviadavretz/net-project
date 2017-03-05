/*
 * PeerMessageListener.cpp
 *
 *  Created on: Mar 5, 2017
 *      Author: user
 */

#include "PeerMessageListener.h"

void PeerMessageListener::openSocket(string otherUsername, string address)
{
//	UDPSocket* newSocket = new UDPSocket(address, SESSION_PORT);
//
//	// Add the socket to the map of sockets.
//	sockets[otherUsername] = newSocket;
}

void PeerMessageListener::closeSocket(string otherUsername)
{
//	UDPSocket* socketToClose = sockets[otherUsername];
//
//	// Close the socket
//	socketToClose->close();
//
//	// Remove the socket from the map of sockets.
//	sockets[otherUsername] = NULL;
}

void PeerMessageListener::closeAllSockets()
{
	// TODO:
}

PeerMessageListener::PeerMessageListener() {}
PeerMessageListener::~PeerMessageListener() {}

