/*
 * MUDPListener.cpp
 *
 *  Created on: Mar 6, 2017
 *      Author: user
 */

#include "MUDPListener.h"

namespace npl {
void MUDPListener::add(UDPSocket* socket){
	sockets.push_back(socket);
}

void MUDPListener::add(vector<UDPSocket*> sockets){
	this->sockets = sockets;
}

UDPSocket* MUDPListener::listen(int timeout){
	fd_set set;
	int nfd = 0;
	FD_ZERO(&set);
	tSockets::iterator iter = sockets.begin();
	for(;iter!= sockets.end();iter++){
		UDPSocket* sock = *iter;
		int fd = sock->getSocketFd();
		FD_SET(fd,&set);
		if (fd >= nfd){
			nfd = fd+1;
		}
	}

	struct timeval tVal = {timeout, 0};
	int rc;

	if (timeout > 0){
		rc = select(nfd, &set,NULL,NULL,&tVal);
	}
	else{
		rc = select(nfd, &set,NULL,NULL,NULL);
	}

	if (rc<1){
		FD_ZERO(&set);
		return NULL;
	}

	iter = sockets.begin();
	for(;iter!= sockets.end();iter++){
		UDPSocket* sock = *iter;
		int fd = sock->getSocketFd();
		if(FD_ISSET(fd,&set)){
			FD_ZERO(&set);
			return sock;
		}
	}
	FD_ZERO(&set);
	return NULL;
}


} /* namespace npl */
