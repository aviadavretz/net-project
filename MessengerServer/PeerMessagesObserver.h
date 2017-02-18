/*
 * PeerMessageReceivedObserver.h
 *
 *  Created on: Feb 18, 2017
 *      Author: user
 */

#ifndef PEERMESSAGESOBSERVER_H_
#define PEERMESSAGESOBSERVER_H_

#include "TCPSocket.h"

using namespace std;
using namespace npl;

class PeerMessagesObserver
{
public:
	virtual void notifyMessageReceived(TCPSocket* peerSocket, string message) = 0;
	virtual ~PeerMessagesObserver() = 0;
};


#endif /* PEERMESSAGESOBSERVER_H_ */
