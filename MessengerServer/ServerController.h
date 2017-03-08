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
#include "strings.h"

using namespace std;
using namespace npl;

class ServerController: public NewPeerAcceptedObserver, PeerMessagesObserver
{
	UserCredentialsManager userCredentialsManager;
	ServerPeersAcceptor peersAcceptor;
	ServerPeersListener peersListener;
	ServerPeersMessageSender peersMessageSender;
	map<TCPSocket*, User*> loggedInUsers;
	vector<Session*> sessions;
	vector<ChatRoom*> chatRooms;
	ServerTerminalPrinter printer;
	map<TCPSocket*, int> peerListeningPorts;

	bool isUserInSession(User* user);
	bool isUserInChatRoom(User* user);
	bool isBusyUser(User* user);
	bool isUserLoggedIn(string username);
	void closeExistingSessions(TCPSocket* peerSocket, User* requestingUser);
	bool closeSession(Session* session);
	string getOtherUsernameBySession(Session* session, string knownUsername);
	ChatRoom* getRoomByUser(User* user);
	Session* getSessionByUser(User* user);
	TCPSocket* getPeerSocketByUsername(string username);
	User* getLoggedInUserByUsername(string username);

public:
	ServerController();
	void startServer();
	void stopServer();
	void notifyNewPeerAccepted(TCPSocket* peerSocket);
	void notifyLoginRequest(TCPSocket* peerSocket, string username, string password);
	void notifyRegistrationRequest(TCPSocket* peerSocket, string username, string password);
	void notifyOpenChatRoomRequest(TCPSocket* peerSocket, string roomName);
	void notifyJoinChatRoomRequest(TCPSocket* peerSocket, string roomName);
	void notifyDisconnectRequest(TCPSocket* peerSocket);
	void notifyCloseSessionOrExitRoomRequest(TCPSocket* peerSocket);
	void notifyCloseChatRoomRequest(TCPSocket* peerSocket, string roomName);
	void notifyOpenSessionRequest(TCPSocket* peerSocket, string otherUserName);
	void notifyListAllUsersRequest(TCPSocket* peerSocket);
	void notifyListAllConnectedUsersRequest(TCPSocket* peerSocket);
	void notifyListAllRoomsRequest(TCPSocket* peerSocket);
	void notifyListAllUsersInRoomRequest(TCPSocket* peerSocket, string roomName);
	void notifyStatusRequest(TCPSocket* peerSocket);
	void notifyListeningPort(TCPSocket* peerSocket, int listeningPort);

	vector<string> getAllRegisteredUsersName();
	vector<string> getAllConnectedUsersName();
	vector<Session*> getAllSessions();
	vector<ChatRoom*> getAllChatRooms();
	ChatRoom* getChatRoomByName(string name);
	User* getUserByPeer(TCPSocket* peer);
	bool isPeerLoggedIn(TCPSocket* peer);
};



#endif /* SERVERCONTROLLER_H_ */
