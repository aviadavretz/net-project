/*
 * ServerController.h
 *
 *  Created on: Feb 7, 2017
 *      Author: user
 */

#ifndef SERVERCONTROLLER_H_
#define SERVERCONTROLLER_H_

#include "MThread.h"
#include "User.h"
#include "Session.h"
#include "string"
#include <vector>

using namespace std;

class ServerController: public MThread
{
	vector<User*> connectedUsers;
	vector<Session*> sessions;
	vector<ChatRoom*> chatRooms;

	bool isUserInSession(User* user);
	bool isUserInChatRoom(User* user);
	bool isBusyUser(User* user);

public:
	ServerController();
	void run();
	vector<User*> getAllUsers();
	vector<User*> getAllConnectedUsers();
	vector<Session*> getAllSessions();
	vector<ChatRoom*> getAllChatRooms();
	ChatRoom* getChatRoomByName(string name);
	void stop();
};



#endif /* SERVERCONTROLLER_H_ */
