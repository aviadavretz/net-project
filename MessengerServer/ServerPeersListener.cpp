/*
 * ServerPeersListener.cpp
 *
 *  Created on: Feb 18, 2017
 *      Author: user
 */

#include "ServerPeersListener.h"

ServerPeersListener::ServerPeersListener(PeerMessagesObserver* observer)
{
	this->observer = observer;
	shouldContinue = true;
}

void ServerPeersListener::run()
{
	while (shouldContinue)
	{
		MTCPListener listener;
		listener.add(peers);

		TCPSocket* readyPeer = listener.listen();

		routeCommand(readCommand(readyPeer));

	}
}

int ServerPeersListener::readCommand(TCPSocket* socket)
{
	int command = 0;
	int bytesReceived = socket->recv((char*)&command, EXPECTED_COMMAND_BYTES_SIZE);

	if (bytesReceived != EXPECTED_COMMAND_BYTES_SIZE)
	{
		return BAD_REQUEST;
	}

	return ntohl((uint32_t)command);
}

void ServerPeersListener::routeCommand(int command)
{

}

void ServerPeersListener::stop()
{
	shouldContinue = false;
}
