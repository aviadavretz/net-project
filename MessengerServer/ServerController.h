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
#include "string"
#include <vector>

using namespace std;
using namespace npl;

class ServerController: public NewPeerAcceptedObserver
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
	vector<string> getAllRegisteredUsersName();
	vector<User*> getAllConnectedUsers();
	vector<Session*> getAllSessions();
	vector<ChatRoom*> getAllChatRooms();
	ChatRoom* getChatRoomByName(string name);
	void notifyNewPeerAccepted(TCPSocket* peerSocket);
	void startServer();
	void stopServer();
};



#endif /* SERVERCONTROLLER_H_ */
