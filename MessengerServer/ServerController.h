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
#include "ServerPeersAcceptor.h"
#include "NewPeerAcceptedObserver.h"
#include "PeerMessagesObserver.h"
#include "ServerPeersListener.h"
#include "string"
#include <vector>
#include <map>
#include <algorithm>
#include "UserCredentialsManager.h"
#include "ServerPeersMessageSender.h"
#include "ServerTerminalPrinter.h"

using namespace std;
using namespace npl;

class ServerController: public NewPeerAcceptedObserver, PeerMessagesObserver
{
	UserCredentialsManager userCredentialsManager;
	ServerPeersAcceptor peersAcceptor;
	ServerPeersListener peersListener;
	ServerPeersMessageSender peersMessageSender;
	map<TCPSocket*, User*> connectedUsers;
	vector<Session*> sessions;
	vector<ChatRoom*> chatRooms;
	ServerTerminalPrinter printer;

	bool isUserInSession(User* user);
	bool isUserInChatRoom(User* user);
	bool isBusyUser(User* user);

public:
	ServerController();
	void startServer();
	void stopServer();
	void notifyNewPeerAccepted(TCPSocket* peerSocket);
	void notifyLoginRequest(TCPSocket* peerSocket, string username, string password);
	void notifyRegistrationRequest(TCPSocket* peerSocket, string username, string password);
	void notifyDisconnectCommand(TCPSocket* peerSocket);
	vector<string> getAllRegisteredUsersName();
	vector<User*> getAllConnectedUsers();
	vector<Session*> getAllSessions();
	vector<ChatRoom*> getAllChatRooms();
	ChatRoom* getChatRoomByName(string name);
	User* getUserByPeer(TCPSocket* peer);
	bool isPeerLoggedIn(TCPSocket* peer);
};



#endif /* SERVERCONTROLLER_H_ */
