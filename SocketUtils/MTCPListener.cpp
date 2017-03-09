/*
 * MTCPListener.cpp
 *
 *  Created on: Mar 20, 2016
 *      Author: user
 */

#include "MTCPListener.h"

namespace npl {
void MTCPListener::add(TCPSocket* socket){
	sockets.push_back(socket);

}

void MTCPListener::add(vector<TCPSocket*> sockets){
	this->sockets = sockets;
}

TCPSocket* MTCPListener::listen(int timeout){
	fd_set set;
	int fdNum = 0;
	FD_ZERO(&set);
	tSockets::iterator iter = sockets.begin();

	for (; iter!= sockets.end(); iter++) {
		TCPSocket* sock = *iter;

		int fd = sock->socket();
		FD_SET(fd,&set);

		if (fd >= fdNum){
			fdNum = fd+1;
		}
	}

	struct timeval tVal = {timeout, 0};
	int readyCount;

	if (timeout > 0) {
		readyCount = select(fdNum, &set,NULL,NULL,&tVal);
	}
	else {
		readyCount = select(fdNum, &set,NULL,NULL,NULL);
	}

	// If there are no ready fds
	if (readyCount<1) {
		FD_ZERO(&set);
		return NULL;
	}

	iter = sockets.begin();

	for (; iter!= sockets.end(); iter++) {
		TCPSocket* sock = *iter;
		int fd = sock->socket();

		// If this fd is set
		if (FD_ISSET(fd,&set)) {
			FD_ZERO(&set);
			return sock;
		}
	}

	// No fd was set
	FD_ZERO(&set);
	return NULL;
}


} /* namespace npl */
