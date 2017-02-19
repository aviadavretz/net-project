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

using namespace std;
using namespace npl;

class ServerPeersMessageSender
{
	void sendCode(TCPSocket* peer, int code);
	void sendMessage(TCPSocket* peer, string message);
public:
	void sendAlreadyLoggedIn(TCPSocket* peer);
	void sendBadUsernamePassword(TCPSocket* peer);
	void sendLoginSuccessful(TCPSocket* peer);
	void sendRegisterFailed(TCPSocket* peer);
	void sendRegisterSuccessful(TCPSocket* peer);
	void sendUsernameExists(TCPSocket* peer);
};

#endif /* SERVERPEERSMESSAGESENDER_H_ */
