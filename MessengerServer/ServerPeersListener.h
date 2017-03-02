/*
 * ServerPeersListener.h
 *
 *  Created on: Feb 18, 2017
 *      Author: user
 */

#ifndef SERVERPEERSLISTENER_H_
#define SERVERPEERSLISTENER_H_

#include "MThread.h"
#include "MTCPListener.h"
#include "TCPSocket.h"
#include "TCPMessengerProtocol.h"
#include "PeerMessagesObserver.h"

using namespace std;
using namespace npl;

class ServerPeersListener: public MThread
{
	vector<TCPSocket*> peers;
	PeerMessagesObserver* observer;
	bool shouldContinue;

	void run();
	int readCommand(TCPSocket* socket);
	void routeCommand(int command, TCPSocket* peer);
	string readMessage(TCPSocket* socket);
	void routeLoginCommand(TCPSocket* peer);
	void routeRegisterCommand(TCPSocket* peer);
	void routeDisconnectCommand(TCPSocket* peer);
	void routeOpenChatRoomCommand(TCPSocket* peer);
	void routeJoinChatRoomCommand(TCPSocket* peer);
	void routeCloseSessionOrExitRoomCommand(TCPSocket* peer);
	void routeCloseChatRoomCommand(TCPSocket* peer);
	void routeOpenSessionCommand(TCPSocket* peer);
	void routeGetAllRegisteredUsers(TCPSocket* peer);
	void routeGetAllConnectedUsers(TCPSocket* peer);
	pair<string, string> getUsernameAndPasswordFromMessage(string message);

public:
	ServerPeersListener(PeerMessagesObserver* observer);
	void addPeer(TCPSocket* peer);
	void removePeer(TCPSocket* peer);
	void stop();
};



#endif /* SERVERPEERSLISTENER_H_ */
