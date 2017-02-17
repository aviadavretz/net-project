/*
 * ChatRoom.cpp
 *
 *  Created on: Feb 17, 2017
 *      Author: user
 */

#include "ChatRoom.h"

ChatRoom::ChatRoom(string name, User* owner)
{
	this->name = name;
	this->owner = owner;
}

string ChatRoom::getName()
{
	return name;
}

User* ChatRoom::getOwner()
{
	return owner;
}

vector<User*> ChatRoom::getParticipatingUsers()
{
	return users;
}
