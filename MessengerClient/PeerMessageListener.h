/*
 * PeerMessageListener.h
 *
 *  Created on: Mar 5, 2017
 *      Author: user
 */

#ifndef PEERMESSAGELISTENER_H_
#define PEERMESSAGELISTENER_H_

#include "SessionMessageObserver.h"
#include "UDPSocket.h"
#include "UDPMessengerProtocol.h"
#include "MThread.h"
#include <map>

using namespace std;
using namespace npl;

class PeerMessageListener: public MThread {
	// Key = username, Value = socket to the user.
	map<string, UDPSocket*> sockets;
	SessionMessageObserver* observer;
	bool shouldContinue;

	void run();
	string readMessage(UDPSocket* socket);
	string getUsernameBySocket(UDPSocket* socket);

public:
	void openSocket(string otherUsername, string address);
	void closeSocket(string otherUsername);
	void closeAllSockets();
	void stop();

	PeerMessageListener(SessionMessageObserver* observer);
	virtual ~PeerMessageListener();
};

#endif /* PEERMESSAGELISTENER_H_ */
