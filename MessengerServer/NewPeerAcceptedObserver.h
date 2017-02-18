/*
 * NewPeerAcceptedObserver.h
 *
 *  Created on: Feb 18, 2017
 *      Author: user
 */

#ifndef NEWPEERACCEPTEDOBSERVER_H_
#define NEWPEERACCEPTEDOBSERVER_H_

#include "TCPSocket.h"

using namespace npl;

class NewPeerAcceptedObserver
{
public:
	virtual void notifyNewPeerAccepted(TCPSocket* peerSocket) = 0;
	virtual ~NewPeerAcceptedObserver() = 0;
};

#endif /* NEWPEERACCEPTEDOBSERVER_H_ */
