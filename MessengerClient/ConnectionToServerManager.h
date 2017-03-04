/*
 * ConnectionToServerManager.h
 *
 *  Created on: Mar 2, 2017
 *      Author: user
 */

#ifndef CONNECTIONTOSERVERMANAGER_H_
#define CONNECTIONTOSERVERMANAGER_H_

#include "TCPSocket.h"
#include "TCPMessengerProtocol.h"

using namespace std;
using namespace npl;

class ConnectionToServerManager {
	TCPSocket* socketToServer;

public:
	int receiveReplyCode();
	string receiveMessage();
	void sendCommandCode(int commandCode);
	void sendArgs(string message);
	void openSocket(string address, int port);
	void closeSocket();
};

#endif /* CONNECTIONTOSERVERMANAGER_H_ */
