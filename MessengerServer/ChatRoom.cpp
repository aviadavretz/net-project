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

void ChatRoom::addParticipant(User* user)
{
	users.push_back(user);
}

void ChatRoom::removeParticipant(User* user)
{
	// TODO: Implement this
}

vector<User*> ChatRoom::getParticipatingUsers()
{
	return users;
}
