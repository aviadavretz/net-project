/*
 * ClientController.h
 *
 *  Created on: Feb 27, 2017
 *      Author: user
 */

#ifndef CLIENTCONTROLLER_H_
#define CLIENTCONTROLLER_H_

#include "string"
#include "ClientTerminalPrinter.h"
#include "ConnectionToServerManager.h"
#include "ServerRepliesObserver.h"
#include "ServerRepliesListener.h"
#include "PeerMessageListener.h"
#include <stdlib.h>

using namespace std;

class ClientController: public ServerRepliesObserver, SessionMessageObserver
{
	ConnectionToServerManager srvConnection;
	ClientTerminalPrinter printer;
	ServerRepliesListener* srvListener;
	PeerMessageListener* peerListener;
	bool connected;

	void sendCommandToServer(int commandCode, string args);
	void sendCommandToServer(int commandCode);

	public:
		ClientController();
		bool isConnected();
		void connect(string address);
		void login(string username, string password);
		void registerUser(string username, string password);
		void openSession(string otherUsername);
		void openRoom(string roomName);
		void joinRoom(string roomName);
		void closeSessionOrExitRoom();
		void closeRoom(string roomName);
		void disconnect();
		void requestAllRegisterdUsersName();
		void requestAllConnectedUsersName();
		void requestAllRooms();
		void requestAllUsersInRoom(string roomName);
		void requestStatus();
		void notifyDisconnected();
		void notifySessionEstablished();
		void notifyChatRoomOpened();
		void notifyJoinedRoom();
		void notifyExitRoom();
		void notifySessionClosed();
		void notifyRoomClosedByOwner();
		void notifyRoomClosedSuccess();
		void notifySomeoneJoinedRoom();
		void notifySomeoneLeftRoom();
		void notifyServerShuttingDown();
		void notifyMessageReceived(string username, string message);
};

#endif /* CLIENTCONTROLLER_H_ */
