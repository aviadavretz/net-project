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

int UDPSocket::getListeningPort()
{
	return listeningPort;
}

UDPSocket::UDPSocket(int port){
	int iteration = 0;
	bool success = false;

	// As long as socket wasn't created
	while (!success && port != 9999)
	{
		// SOCK_DGRAM = UDP
		socket_fd = socket (AF_INET, SOCK_DGRAM, 0);
		struct sockaddr_in s_in;

		// Clear the s_in struct
		bzero((char *) &s_in, sizeof(s_in));

		// Set the s_in address
		s_in.sin_family = (short)AF_INET;
		s_in.sin_addr.s_addr = htonl(INADDR_ANY);    /* WILDCARD any system ip*/
		s_in.sin_port = htons(port);

		// Try to bind to the specified address
		if (bind(socket_fd, (struct sockaddr *)&s_in, sizeof(s_in)) < 0){
			// Close this socket and try again on the next port.
			::close(socket_fd);
			port++;
		}
		else
		{
			// Succeeded
			listeningPort = port;
			success = true;
			cout << "UDPSocket opened on port " << port << endl;
		}
	}
}

int UDPSocket::recv(char* buffer, int length){
	socklen_t fromSize = sizeof(from);

	// Receive the message into the buffer
	int bytesRead = recvfrom(socket_fd, buffer, length, 0,(sockaddr*)&from,&fromSize);

	// While nothing was read
	while (bytesRead <= 0)
	{
		bytesRead = recvfrom(socket_fd, buffer, length, 0,(sockaddr*)&from,&fromSize);
	}

	return bytesRead;
}

int UDPSocket::sendTo(const string& msg,const string& ip, int port){
	struct sockaddr_in s_in;

	// Clear the s_in struct
	bzero((char *) &s_in, sizeof(s_in));

	// Initialize the address
	s_in.sin_family = (short)AF_INET;
	s_in.sin_addr.s_addr = inet_addr(ip.c_str());
	s_in.sin_port = htons(port);

	// Send the message to the specified s_in address
	int sentBytes = sendto(socket_fd,msg.c_str(), msg.length(),0,(struct sockaddr *)&s_in,sizeof(s_in));
	return sentBytes;
}

int UDPSocket::reply(const string& msg){
	cout<<"reply "<<msg<<" "<< endl;
	socklen_t fromSize = sizeof(from);
	int rc = sendto(socket_fd,msg.c_str(), msg.length(),0,(struct sockaddr *)&from,fromSize);
	return rc;
}

void UDPSocket::close(){
	shutdown(socket_fd,SHUT_RDWR);
	::close(socket_fd);
}

string UDPSocket::fromAddr(){
	return inet_ntoa(from.sin_addr);
}




