/*
 * ServerPeersAcceptor.h
 *
 *  Created on: Feb 18, 2017
 *      Author: user
 */

#ifndef SERVERPEERSACCEPTOR_H_
#define SERVERPEERSACCEPTOR_H_

#include "MThread.h"
#include "TCPSocket.h"
#include "TCPMessengerProtocol.h"
#include "NewPeerAcceptedObserver.h"

using namespace std;
using namespace npl;

class ServerPeersAcceptor: public MThread
{
	TCPSocket* acceptingSocket;
	NewPeerAcceptedObserver* observer;
	bool shouldContinue;

	void run();

public:
	ServerPeersAcceptor(NewPeerAcceptedObserver* observer);
	void stop();
	void closeSockets();
};

#endif /* SERVERPEERSACCEPTOR_H_ */
