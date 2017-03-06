/*
 * PeerInfo.h
 *
 *  Created on: Mar 6, 2017
 *      Author: user
 */

#ifndef PEERINFO_H_
#define PEERINFO_H_

#include "string"

using namespace std;

class PeerInfo
{
	string username;
	string ip;
	int port;

public:
	PeerInfo(string username, string ip, int port);
	string getUsername();
	string getIp();
	int getPort();
};



#endif /* PEERINFO_H_ */
