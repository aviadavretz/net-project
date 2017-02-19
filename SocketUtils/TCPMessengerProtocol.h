/*
 * TCPMessengerProtocol.h
 *
 *  Created on: Feb 13, 2013
 *      Author: efi
 */

#ifndef TCPMESSENGERPROTOCOL_H_
#define TCPMESSENGERPROTOCOL_H_

/**
 * TCP Messenger protocol:
 * all messages are of the format [Command 4 byte int]
 * and optionally data follows in the format [Data length 4 byte int][ Data ]
 */
#define MSNGR_PORT 3346

#define CLOSE_SESSION_WITH_PEER 	1
#define OPEN_SESSION_WITH_PEER 		2
#define EXIT						3
#define SEND_MSG_TO_PEER			4
#define SESSION_REFUSED				5
#define SESSION_ESTABLISHED			6

// Client commands

#define GET_REGISTERED_USERS 		7
#define GET_CONNECTED_USERS			8
#define GET_CHAT_ROOMS				9
#define GET_USERS_IN_CHAT_ROOM		10
#define ENTER_CHAT_ROOM				11
#define CLOSE_CHAT_ROOM				12
#define DISCONNECT					13

#define LOGIN					    70
#define REGISTER					71
#define USERNAME_PASSWORD_DELIMITER " "

// Server responses

#define ALREADY_LOGGED_IN 200
#define BAD_USERNAME_PASSWORD 201
#define LOGIN_SUCCEEDED 202
#define REGISTER_FAILURE 203
#define REGISTER_SUCCEEDED 204
#define USERNAME_EXISTS 205

#define EXPECTED_COMMAND_BYTES_SIZE 				 4
#define EXPECTED_MESSAGE_LENGTH_INDICATOR_BYTES_SIZE 4

#define TEST_PEER_NAME "test"
#define SESSION_REFUSED_MSG "Connection to peer refused, peer might be busy or disconnected, try again later"



#endif /* TCPMESSENGERPROTOCOL_H_ */
