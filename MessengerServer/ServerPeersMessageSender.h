/*
 * ServerPeersSender.h
 *
 *  Created on: Feb 19, 2017
 *      Author: user
 */

#ifndef SERVERPEERSMESSAGESENDER_H_
#define SERVERPEERSMESSAGESENDER_H_

#include "TCPSocket.h"
#include "TCPMessengerProtocol.h"
#include <sstream>
#include <vector>
#include "string"
#include "User.h"

using namespace std;
using namespace npl;

class ServerPeersMessageSender
{
	void sendCode(TCPSocket* peer, int code);
//	void sendMessage(TCPSocket* peer, string message);
	void sendStringList(TCPSocket* peer, int code, vector<string> strings);
	void sendOpenSessionSuccess(TCPSocket* peer);

public:
	void sendServerShuttingDown(TCPSocket* peer);
	void sendMessage(TCPSocket* peer, string message);
	// TODO: Don't really need all these functions, only: sendCode(TCPSocket* peer, int code) and a bunch of constants
	void sendClientAlreadyLoggedIn(TCPSocket* peer);
	void sendUserAlreadyLoggedIn(TCPSocket* peer);
	void sendNotLoggedIn(TCPSocket* peer);
	void sendBadUsernamePassword(TCPSocket* peer);
	void sendLoginSuccessful(TCPSocket* peer);
	void sendRegisterFailed(TCPSocket* peer);
	void sendRegisterSuccessful(TCPSocket* peer);
	void sendUsernameExists(TCPSocket* peer);
	void sendConnectSuccess(TCPSocket* peer);
	void sendDisconnectSuccess(TCPSocket* peer);
	void sendRoomNameExists(TCPSocket* peer);
	void sendOpenRoomSuccess(TCPSocket* peer, string roomName);
	void sendRoomDoesntExist(TCPSocket* peer);
	void sendJoinRoomSuccess(TCPSocket* peer);
	void sendAlreadyBusy(TCPSocket* peer);
	void sendExitRoomSuccess(TCPSocket* peer);
	void sendCloseSessionSuccess(TCPSocket* peer, string otherUsername);
	void sendNotInSessionOrRoom(TCPSocket* peer);
	void sendNotRoomOwner(TCPSocket* peer);
	void sendCloseRoomSuccess(TCPSocket* peer);
	void sendSessionWithSelf(TCPSocket* peer);
	void sendUserNotFound(TCPSocket* peer);
	void sendOtherUserBusy(TCPSocket* peer);
	void sendAllRegisterdUsers(TCPSocket* peer, vector<string> usernames);
	void sendAllConnectedUsers(TCPSocket* peer, vector<string> usernames);
	void sendAllRooms(TCPSocket* peer, vector<string> rooms);
	void sendAllUsersInRoom(TCPSocket* peer, vector<string> usernames);
	void sendStatusFree(TCPSocket* peer);
	void sendStatusInARoom(TCPSocket* peer);
	void sendStatusInASession(TCPSocket* peer);
	void sendConnectionData(TCPSocket* first, string firstUsername, int firstListenPort,
							TCPSocket* second, string secondUsername, int secondListenPort);
	void sendEstablishedSessionCommunicationDetails(TCPSocket* initiatingPeer, User* initiatingUser, int initiatingListenPort,
												    TCPSocket* receivingPeer, User* receivingUser, int receivingListenPort);
	void sendSomeoneJoinedRoom(TCPSocket* peer);
	void sendSomeoneLeftRoom(TCPSocket* peer, string leavingUsername);
	void sendRoomWasClosed(TCPSocket* peer, string roomName);
};

#endif /* SERVERPEERSMESSAGESENDER_H_ */
