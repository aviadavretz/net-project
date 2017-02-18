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
#include "ServerController.h"

using namespace std;
using namespace npl;

class ServerPeersAcceptor: public MThread
{
	TCPSocket* serverSocket;
	ServerController* controller;
	bool shouldContinue;

	void run();

public:
	ServerPeersAcceptor(ServerController* controller);
	~ServerPeersAcceptor();
};

#endif /* SERVERPEERSACCEPTOR_H_ */
