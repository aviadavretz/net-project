/*
 * RepliesFromServerObserver.h
 *
 *  Created on: Mar 4, 2017
 *      Author: user
 */

#ifndef SERVERREPLIESOBSERVER_H_
#define SERVERREPLIESOBSERVER_H_

using namespace std;
using namespace npl;

class ServerRepliesObserver
{
public:
	virtual void notifySessionEstablished() = 0;
	virtual void notifyChatRoomOpened() = 0;
	virtual void notifyJoinedRoom() = 0;
	virtual void notifyExitRoom() = 0;
	virtual void notifySessionClosed() = 0;
	virtual void notifyRoomClosed() = 0;
	virtual void notifyDisconnected() = 0;
	virtual ~ServerRepliesObserver() = 0;
};

#endif /* SERVERREPLIESOBSERVER_H_ */
