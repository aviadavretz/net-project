/*
 * PeerMessageListener.h
 *
 *  Created on: Mar 5, 2017
 *      Author: user
 */

#ifndef PEERMESSAGELISTENER_H_
#define PEERMESSAGELISTENER_H_

#include "UDPSocket.h"
#include "UDPMessengerProtocol.h"
#include <map>

using namespace std;
using namespace npl;

class PeerMessageListener {
	// Key = username, Value = socket to the user.
	map<string, UDPSocket*> sockets;

public:
	void openSocket(string otherUsername, string address);
	void closeSocket(string otherUsername);
	void closeAllSockets();

	PeerMessageListener();
	virtual ~PeerMessageListener();
};

#endif /* PEERMESSAGELISTENER_H_ */
