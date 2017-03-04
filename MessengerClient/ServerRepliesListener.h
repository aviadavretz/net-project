/*
 * RepliesFromServerListener.h
 *
 *  Created on: Mar 4, 2017
 *      Author: user
 */

#ifndef SERVERREPLIESLISTENER_H_
#define SERVERREPLIESLISTENER_H_

#include "MThread.h"
#include "ConnectionToServerManager.h"
#include "ClientTerminalPrinter.h"
#include "ServerRepliesObserver.h"
#include <stdlib.h>

using namespace std;
using namespace npl;

class ServerRepliesListener: public MThread
{
	bool shouldContinue;
	ConnectionToServerManager* connection;
	ClientTerminalPrinter* printer;
	ServerRepliesObserver* observer;

	void run();

public:
	ServerRepliesListener(ConnectionToServerManager* connection, ClientTerminalPrinter* printer, ServerRepliesObserver* observer);
	void stop();
};

#endif /* SERVERREPLIESLISTENER_H_ */
