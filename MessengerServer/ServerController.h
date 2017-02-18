/*
 * ServerController.h
 *
 *  Created on: Feb 7, 2017
 *      Author: user
 */

#ifndef SERVERCONTROLLER_H_
#define SERVERCONTROLLER_H_

#include "MThread.h"
#include "TCPSocket.h"
#include "User.h"
#include "Session.h"
#include "ChatRoom.h"
#include "LoginManager.h"
#include "ServerPeersAcceptor.h"
#include "NewPeerAcceptedObserver.h"
#include "PeerMessagesObserver.h"
#include "string"
#include <vector>

using namespace std;
using namespace npl;

class ServerController: public NewPeerAcceptedObserver, PeerMessagesObserver
{
	LoginManager loginManager;
	ServerPeersAcceptor peersAcceptor;
	vector<User*> connectedUsers;
	vector<Session*> sessions;
	vector<ChatRoom*> chatRooms;

	bool isUserInSession(User* user);
	bool isUserInChatRoom(User* user);
	bool isBusyUser(User* user);

public:
	ServerController();
	void startServer();
	void stopServer();
	void notifyNewPeerAccepted(TCPSocket* peerSocket);
	void notifyMessageReceived(TCPSocket* peerSocket, string message);
	vector<string> getAllRegisteredUsersName();
	vector<User*> getAllConnectedUsers();
	vector<Session*> getAllSessions();
	vector<ChatRoom*> getAllChatRooms();
	ChatRoom* getChatRoomByName(string name);
};



#endif /* SERVERCONTROLLER_H_ */
