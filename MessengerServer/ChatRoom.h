/*
 * ChatRoom.h
 *
 *  Created on: Feb 7, 2017
 *      Author: user
 */

#ifndef CHATROOM_H_
#define CHATROOM_H_

#include "User.h"
#include <vector>

class ChatRoom
{
	string name;
	vector<User*> users;
	User* owner;

public:
	ChatRoom(string name, User* owner);
	string getName();
	User* getOwner();
	vector<User*> getParticipatingUsers();
};



#endif /* CHATROOM_H_ */
