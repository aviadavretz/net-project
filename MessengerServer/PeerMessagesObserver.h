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
	virtual void notifyOpenChatRoomRequest(TCPSocket* peerSocket, string roomName) = 0;
	virtual void notifyJoinChatRoomRequest(TCPSocket* peerSocket, string roomName) = 0;
	virtual void notifyDisconnectRequest(TCPSocket* peerSocket) = 0;
	virtual void notifyCloseSessionOrExitRoomRequest(TCPSocket* peerSocket) = 0;
	virtual void notifyCloseChatRoomRequest(TCPSocket* peerSocket, string roomName) = 0;
	virtual void notifyOpenSessionRequest(TCPSocket* peerSocket, string otherUserName) = 0;
	virtual void notifyListAllUsersRequest(TCPSocket* peerSocket) = 0;
	virtual void notifyListAllConnectedUsersRequest(TCPSocket* peerSocket) = 0;
	virtual void notifyListAllRoomsRequest(TCPSocket* peerSocket) = 0;
	virtual void notifyListAllUsersInRoomRequest(TCPSocket* peerSocket, string roomName) = 0;
	virtual void notifyStatusRequest(TCPSocket* peerSocket) = 0;
	virtual ~PeerMessagesObserver() = 0;
};


#endif /* PEERMESSAGESOBSERVER_H_ */
