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

TCPSocket* MTCPListener::listen(int timeout) {
	// Create an fd_set and clear it
	fd_set set;
	FD_ZERO(&set);
	// 1 + highest socketId (FD)
	int nfds = 0;

	tSockets::iterator iter = sockets.begin();

	for (; iter!= sockets.end(); iter++) {
		TCPSocket* sock = *iter;

		// Insert the current fd into the fd_set
		int fd = sock->socket();
		FD_SET(fd,&set);

		// Save the largest fd
		if (fd >= nfds){
			nfds = fd+1;
		}
	}

	struct timeval tVal = {timeout, 0};
	int readyCount;

	// Check which fd from the fd_set is available for read.
	if (timeout > 0) {
		readyCount = select(fdNum, &set,NULL,NULL,&tVal);
	}
	else {
		readyCount = select(fdNum, &set,NULL,NULL,NULL);
	}

	// If there are no ready fds
	if (readyCount<1) {
		// Clear the set
		FD_ZERO(&set);
		return NULL;
	}

	iter = sockets.begin();

	for (; iter!= sockets.end(); iter++) {
		TCPSocket* sock = *iter;
		int fd = sock->socket();

		// If this fd is available for read
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
