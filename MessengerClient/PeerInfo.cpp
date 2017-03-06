/*
 * PeerInfo.cpp
 *
 *  Created on: Mar 6, 2017
 *      Author: user
 */

#include "PeerInfo.h"

PeerInfo::PeerInfo(string username, string ip, int port) : username(username), ip(ip), port(port) {}

string PeerInfo::getUsername()
{
	return username;
}

string PeerInfo::getIp()
{
	return ip;
}

int PeerInfo::getPort()
{
	return port;
}
