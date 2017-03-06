/*
 * MUDPListener.h
 *
 *  Created on: Mar 6, 2017
 *      Author: user
 */

#ifndef MUDPLISTENER_H_
#define MUDPLISTENER_H_

#include "UDPSocket.h"
#include <vector>

using namespace std;
namespace npl {

class MUDPListener {
	typedef vector<UDPSocket*> tSockets;
	vector<UDPSocket*> sockets;

public:
	/**
	 * add socket to listen to
	 */
	void add(UDPSocket* socket);
	void add(vector<UDPSocket*> sockets);
	UDPSocket* listen(int timeout = 0);
};

} /* namespace npl */

#endif /* MUDPLISTENER_H_ */
