/*
 * ClientController.h
 *
 *  Created on: Feb 27, 2017
 *      Author: user
 */

#ifndef CLIENTCONTROLLER_H_
#define CLIENTCONTROLLER_H_

#include "string"
#include "TCPSocket.h"
#include "ClientTerminalPrinter.h"

using namespace std;
using namespace npl;

class ClientController
{
	TCPSocket* socketToServer;
	ClientTerminalPrinter printer;
	bool connected;

	void manageReply(int replyCode, string relevantData);
	int receiveReplyCode();
	void sendCommandCode(int commandCode);
	void sendArgs(string message);
	void closeSocket();

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
};

#endif /* CLIENTCONTROLLER_H_ */
