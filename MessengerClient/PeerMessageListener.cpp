/*
 * PeerMessageListener.cpp
 *
 *  Created on: Mar 5, 2017
 *      Author: user
 */

#include "PeerMessageListener.h"
#include <algorithm>

PeerMessageListener::PeerMessageListener(SessionMessageObserver* observer)
{
	this->observer = observer;
	this->shouldContinue = true;

	// Open the session socket, We'll be using it for receiving and sending messages to/from peers
	this->sessionSocket = new UDPSocket(SESSION_PORT);
}

bool PeerMessageListener::arePeersEmpty()
{
	return peers.size() == 0;
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

string PeerMessageListener::readMessage()
{
	char messageContent[MESSAGE_LENGTH];

	// Receiving the message content
	sessionSocket->recv(messageContent, MESSAGE_LENGTH);
	messageContent[MESSAGE_LENGTH] = '\0';

	return string(messageContent);
}

void PeerMessageListener::sendMessage(string message)
{
	// Go over all of the peers to which we connected
	for (vector<PeerInfo*>::iterator iterator = peers.begin(); iterator != peers.end(); iterator++)
	{
		// Send the message to every one
		PeerInfo* peerInfo = *iterator;
		sessionSocket->sendTo(message, peerInfo->getIp(), peerInfo->getPort());
	}
}

void PeerMessageListener::addPeer(string username, string ip, int port)
{
	PeerInfo* newPeer = new PeerInfo(username, ip, port);
	peers.push_back(newPeer);
}

void PeerMessageListener::removePeerByUsername(string username)
{
	for (vector<PeerInfo*>::iterator iterator = peers.begin(); iterator != peers.end(); iterator++)
	{
		PeerInfo* peerInfo = *iterator;

		// Check if the current entry is the one we would like to remove
		if (peerInfo != NULL && username.compare(peerInfo->getUsername()) == 0)
		{
			removePeer(peerInfo);
			break;
		}
	}
}

void PeerMessageListener::removePeer(PeerInfo* peer)
{
	// TODO: Implement this without #include <algorithm>?
	vector<PeerInfo*>::iterator position = std::find(peers.begin(), peers.end(), peer);

	 // end() means the element was not found
	if (position != peers.end())
	{
		peers.erase(position);
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

