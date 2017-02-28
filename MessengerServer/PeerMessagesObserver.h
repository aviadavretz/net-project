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
	virtual void notifyLoginRequest(TCPSocket* peerSocket, string username, string password) = 0;
	virtual void notifyRegistrationRequest(TCPSocket* peerSocket, string username, string password) = 0;
	virtual void notifyDisconnectCommand(TCPSocket* peerSocket) = 0;
	virtual ~PeerMessagesObserver() = 0;
};


#endif /* PEERMESSAGESOBSERVER_H_ */
