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
#include <stdlib.h>

using namespace std;

class ClientController
{
	ConnectionToServerManager srvConnection;
	ClientTerminalPrinter printer;
	bool connected;

	int sendCommandWithArgsToServerAndReceiveReply(int commandCode, string args);
	int sendCommandToServerAndReceiveReply(int commandCode);

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
};

#endif /* CLIENTCONTROLLER_H_ */
