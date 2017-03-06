/*
 * UDPSocket.cpp
 *
 *  Created on: Feb 8, 2013
 *      Author: Eliav Menachi
 */

#include "UDPSocket.h"
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>

using namespace npl;

int listeningPort = 9999;

int UDPSocket::getListeningPort()
{
	return listeningPort;
}

UDPSocket::UDPSocket(int port){
	int iteration = 0;
	bool success = false;

	while (!success && port != 9999)
	{
		// SOCK_DGRAM = UDP
		socket_fd = socket (AF_INET, SOCK_DGRAM, 0);
		struct sockaddr_in  s_in;
		bzero((char *) &s_in, sizeof(s_in));
		s_in.sin_family = (short)AF_INET;
		s_in.sin_addr.s_addr = htonl(INADDR_ANY);    /* WILDCARD any system ip*/
		s_in.sin_port = htons(port);

		if (bind(socket_fd, (struct sockaddr *)&s_in, sizeof(s_in))<0){
			// Close this socket and try again on the next port.
			::close(socket_fd);
			port++;
		}
		else
		{
			listeningPort = port;
			success = true;
			cout << "Socket opened on port " << port << endl;
		}
	}
}

int UDPSocket::recv(char* buffer, int length){
	socklen_t fromSize = sizeof(from);

	int rc = recvfrom(socket_fd, buffer, length, 0,(sockaddr*)&from,&fromSize);

	while (rc < 0)
	{
		rc = recvfrom(socket_fd, buffer, length, 0,(sockaddr*)&from,&fromSize);
	}

	return rc;
}

int UDPSocket::sendTo(const string& msg,const string& ip, int port){
	struct sockaddr_in  s_in;
	bzero((char *) &s_in, sizeof(s_in));
	s_in.sin_family = (short)AF_INET;
	s_in.sin_addr.s_addr = inet_addr(ip.c_str());
	s_in.sin_port = htons(port);

	int rc = sendto(socket_fd,msg.c_str(), msg.length(),0,(struct sockaddr *)&s_in,sizeof(s_in));
	return rc;
}

int UDPSocket::reply(const string& msg){
	cout<<"reply "<<msg<<" "<< endl;
	socklen_t fromSize = sizeof(from);
	int rc = sendto(socket_fd,msg.c_str(), msg.length(),0,(struct sockaddr *)&from,fromSize);
	return rc;
}

void UDPSocket::close(){
	cout<<"closing socket"<<endl;
	shutdown(socket_fd,SHUT_RDWR);
	::close(socket_fd);
}

string UDPSocket::fromAddr(){
	return inet_ntoa(from.sin_addr);
}




