/*
 * SessionMessageObserver.h
 *
 *  Created on: Mar 6, 2017
 *      Author: user
 */

#ifndef SESSIONMESSAGEOBSERVER_H_
#define SESSIONMESSAGEOBSERVER_H_

#include "string"
using namespace std;

class SessionMessageObserver
{
public:
	virtual void notifyMessageReceived(string username, string message) = 0;
	virtual ~SessionMessageObserver() = 0;
};


#endif /* SESSIONMESSAGEOBSERVER_H_ */
