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

using namespace std;
using namespace npl;

class ServerPeersMessageSender
{
	void sendCode(TCPSocket* peer, int code);
	void sendMessage(TCPSocket* peer, string message);
	void sendStringList(TCPSocket* peer, int code, vector<string> strings);
public:
	// TODO: Don't really need all these functions, only: sendCode(TCPSocket* peer, int code) and a bunch of constants
	void sendAlreadyLoggedIn(TCPSocket* peer);
	void sendNotLoggedIn(TCPSocket* peer);
	void sendBadUsernamePassword(TCPSocket* peer);
	void sendLoginSuccessful(TCPSocket* peer);
	void sendRegisterFailed(TCPSocket* peer);
	void sendRegisterSuccessful(TCPSocket* peer);
	void sendUsernameExists(TCPSocket* peer);
	void sendConnectSuccess(TCPSocket* peer);
	void sendDisconnectSuccess(TCPSocket* peer);
	void sendRoomNameExists(TCPSocket* peer);
	void sendOpenRoomSuccess(TCPSocket* peer);
	void sendRoomDoesntExist(TCPSocket* peer);
	void sendJoinRoomSuccess(TCPSocket* peer);
	void sendAlreadyBusy(TCPSocket* peer);
	void sendExitRoomSuccess(TCPSocket* peer);
	void sendCloseSessionSuccess(TCPSocket* peer);
	void sendNotInSessionOrRoom(TCPSocket* peer);
	void sendNotRoomOwner(TCPSocket* peer);
	void sendCloseRoomSuccess(TCPSocket* peer);
	void sendUserNotFound(TCPSocket* peer);
	void sendOtherUserBusy(TCPSocket* peer);
	void sendOpenSessionSuccess(TCPSocket* peer);
	void sendAllRegisterdUsers(TCPSocket* peer, vector<string> usernames);
	void sendAllConnectedUsers(TCPSocket* peer, vector<string> usernames);
};

#endif /* SERVERPEERSMESSAGESENDER_H_ */
