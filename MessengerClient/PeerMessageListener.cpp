/*
 * PeerMessageListener.cpp
 *
 *  Created on: Mar 5, 2017
 *      Author: user
 */

#include "PeerMessageListener.h"

PeerMessageListener::PeerMessageListener(SessionMessageObserver* observer)
{
	this->observer = observer;
	this->shouldContinue = true;

	// Open the session socket, We'll be using it for receiving and sending messages to/from peers
	this->sessionSocket = new UDPSocket(SESSION_PORT);
}

int PeerMessageListener::getListeningPort()
{
	return sessionSocket->getListeningPort();
}

void PeerMessageListener::run()
{
	while (shouldContinue)
	{
		// Try to receive a message
		string message = readMessage();

		observer->notifyMessageReceived(message);
	}
}

// TODO : This message sending/reading implementation is not safe.
// 	      Multiple clients can send a message at the same time which can make things mix up.
//        Maybe sending the message in one piece (without first stating what's the size in bytes) can fix that.
string PeerMessageListener::readMessage()
{
	char messageContent[256];
	int messageLength = 256;

//	// Receiving message length
//	sessionSocket->recv((char*)&messageLength, EXPECTED_MESSAGE_LENGTH_INDICATOR_BYTES_SIZE);
//	messageLength = ntohl(messageLength);

	// Receiving the message content
	sessionSocket->recv(messageContent, messageLength);
	messageContent[messageLength] = '\0';

	return string(messageContent);
}

void PeerMessageListener::sendMessage(string message)
{
	// Go over all of the peers to which we connected
	for (vector<PeerInfo>::iterator iterator = peers.begin(); iterator != peers.end(); iterator ++)
	{
		// Send the message to every one
		PeerInfo peerInfo = *iterator;
		sessionSocket->sendTo(message, peerInfo.getIp(), peerInfo.getPort());
	}
}

void PeerMessageListener::addPeer(string username, string ip, int port)
{
	peers.push_back(PeerInfo(username, ip, port));
}

void PeerMessageListener::removePeerByUsername(string username)
{
	for (vector<PeerInfo>::iterator iterator = peers.begin(); iterator != peers.end(); iterator++)
	{
		PeerInfo peerInfo = *iterator;

		// Check if the current entry is the one we would like to remove
		if (peerInfo.getUsername().compare(username) == 0)
		{
			peers.erase(iterator);
		}
	}
}

void PeerMessageListener::removeAllPeers()
{
	peers.clear();
}

/**
 * This function should only be called when disconnecting
 */
void PeerMessageListener::stop()
{
	shouldContinue = false;
	sessionSocket->close();
	delete sessionSocket;
}

PeerMessageListener::~PeerMessageListener() {}

