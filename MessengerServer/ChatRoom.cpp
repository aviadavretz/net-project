/*
 * ChatRoom.cpp
 *
 *  Created on: Feb 17, 2017
 *      Author: user
 */

#include "ChatRoom.h"
#include <algorithm>

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
	// TODO: Implement this without #include <algorithm>?
	vector<User*>::iterator position = std::find(users.begin(), users.end(), user);

	 // end() means the element was not found
	if (position != users.end())
	{
		users.erase(position);
	}
}

vector<User*> ChatRoom::getParticipatingUsers()
{
	return users;
}
