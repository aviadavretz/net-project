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
#include <vector>
#include "PeerInfo.h"

using namespace std;
using namespace npl;

class PeerMessageListener: public MThread {
	vector<PeerInfo*> peers;
	SessionMessageObserver* observer;
	UDPSocket* sessionSocket;
	bool shouldContinue;

	void run();
	string readMessage();
	void removePeer(PeerInfo* peer);

public:
	void sendMessage(string message);
	void addPeer(string username, string ip, int port);
	void removePeerByUsername(string username);
	void removeAllPeers();
	void stop();
	int getListeningPort();

	PeerMessageListener(SessionMessageObserver* observer);
	virtual ~PeerMessageListener();
};

#endif /* PEERMESSAGELISTENER_H_ */
