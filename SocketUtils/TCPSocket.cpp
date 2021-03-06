/*
 * TCPSocket.cpp
 *
 *  Created on: Feb 6, 2013
 *      Author: Eliav Menachi
 */


#include "TCPSocket.h"
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>

using namespace std;
using namespace npl;

TCPSocket::TCPSocket(int connected_sock,struct sockaddr_in serverAddr,struct sockaddr_in peerAddr){
	this->serverAddr =  serverAddr;
	this->peerAddr =  peerAddr;
	socket_fd = connected_sock;
}

TCPSocket::TCPSocket(int port){
	/**
	 * int socket(int domain, int type, int protocol);
	 * creates a TCP socket
	 * AF_INET - IPv4 Internet protocols
	 * SOCK_STREAM - TCP
	 * 0 - default protocol type
	 */
	socket_fd = ::socket(AF_INET, SOCK_STREAM, 0);

	// Clear the s_in struct
	bzero((char *) &serverAddr, sizeof(serverAddr));

	// Set the sin address
	serverAddr.sin_family = (short)AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);    /* WILDCARD */
	serverAddr.sin_port = htons((u_short)port);

	// Try to bind the socket on the specified address
	printf("TCP server binding...\n");
	if (bind(socket_fd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
	{
		perror ("Error naming channel");
	}
}

TCPSocket::TCPSocket(const string& peerIp, int port){
	/**
	 * int socket(int domain, int type, int protocol);
	 * creates a TCP socket
	 * AF_INET - IPv4 Internet protocols
	 * SOCK_STREAM - TCP
	 * 0 - default protocol type
	 */
	socket_fd = ::socket (AF_INET, SOCK_STREAM, 0);

	// Clear the s_in struct
	bzero((char *) &peerAddr, sizeof(peerAddr));

	// Set the sin address
	peerAddr.sin_family = (short)AF_INET;
	peerAddr.sin_addr.s_addr = inet_addr(peerIp.data());
	peerAddr.sin_port = htons((u_short)port);

	// Try to connect to the peerAddr
	if (connect(socket_fd, (struct sockaddr *)&peerAddr, sizeof(peerAddr)) < 0)
	{
		perror ("Error establishing communications");
		::close(socket_fd);
	}
}


TCPSocket* TCPSocket::listenAndAccept(){
	// Listen to incoming connections
	int status = listen(socket_fd, 1);

	// If there was no new connection
	if (status<0) {
		return NULL;
	}

	// Reset the peerAddr to zeros
	socklen_t len = sizeof(peerAddr);
	bzero((char *) &peerAddr, sizeof(peerAddr));

	// Accept the new connection and create a new socket
	int connect_sock = accept(socket_fd, (struct sockaddr *)&peerAddr, &len);
	return new TCPSocket(connect_sock,serverAddr,peerAddr);
}


int TCPSocket::recv(char* buffer, int length){
	return ::recv(socket_fd,buffer,length,0);
}


int TCPSocket::send(const string& msg){
	return ::send(socket_fd,msg.c_str(),msg.size(),0);
}

int TCPSocket::send(const char* msg, int length){
	return ::send(socket_fd, msg, length,0);
}


void TCPSocket::close(){
	shutdown(socket_fd,SHUT_RDWR);
	::close(socket_fd);
}


string TCPSocket::fromAddr(){
	return inet_ntoa(peerAddr.sin_addr);
}

int TCPSocket::socket(){
	return socket_fd;
}
