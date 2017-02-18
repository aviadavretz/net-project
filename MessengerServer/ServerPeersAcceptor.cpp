/*
 * ServerTCPListener.cpp
 *
 *  Created on: Feb 18, 2017
 *      Author: user
 */

#include "ServerPeersAcceptor.h"

ServerPeersAcceptor::ServerPeersAcceptor(ServerController* controller)
{
	this->controller = controller;
	serverSocket = new TCPSocket(MSNGR_PORT);
	shouldContinue = true;

	start();
}

void ServerPeersAcceptor::run()
{
	while (shouldContinue)
	{
		TCPSocket* peer = serverSocket->listenAndAccept();
		cout << "New peer accepted from address : " << peer->fromAddr() << " !" << endl;

		//controller->addNewPeer(peer);
	}
}

ServerPeersAcceptor::~ServerPeersAcceptor()
{
	shouldContinue = false;
	serverSocket->close();
}
