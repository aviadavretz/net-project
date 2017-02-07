/*
 * Session.h
 *
 *  Created on: Feb 7, 2017
 *      Author: user
 */

#ifndef SESSION_H_
#define SESSION_H_

#include "User.h"

class Session
{
	User* firstUser;
	User* secondUser;

public:
	Session(User* firsUser, User* secondUser);
	User* getFirstUser();
	User* getSecondUser();
};


#endif /* SESSION_H_ */
