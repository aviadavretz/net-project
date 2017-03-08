/*
 * ServerTCPListener.cpp
 *
 *  Created on: Feb 18, 2017
 *      Author: user
 */

#include "ServerPeersAcceptor.h"

ServerPeersAcceptor::ServerPeersAcceptor(NewPeerAcceptedObserver* observer)
{
	this->observer = observer;
	acceptingSocket = new TCPSocket(MSNGR_PORT);
	shouldContinue = true;
}

void ServerPeersAcceptor::run()
{
	while (shouldContinue)
	{
		TCPSocket* peerSocket = acceptingSocket->listenAndAccept();
		observer->notifyNewPeerAccepted(peerSocket);
	}
}

void ServerPeersAcceptor::stop()
{
	shouldContinue = false;
}

void ServerPeersAcceptor::closeSockets()
{
	// After stopped, close & delete the socket.
	acceptingSocket->close();
	delete acceptingSocket;
}
