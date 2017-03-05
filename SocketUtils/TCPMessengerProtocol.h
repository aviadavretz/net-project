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

#define GET_REGISTERED_USERS 7
#define GET_CONNECTED_USERS	8
#define GET_CHAT_ROOMS 9
#define GET_USERS_IN_CHAT_ROOM 10
#define OPEN_CHAT_ROOM 11
#define CLOSE_CHAT_ROOM	12
#define DISCONNECT 13
#define JOIN_CHAT_ROOM 14
#define CLOSE_SESSION_OR_EXIT_ROOM 15
#define CLOSE_ROOM 16
#define GET_STATUS 17

#define LOGIN 70
#define REGISTER 71
#define USERNAME_PASSWORD_DELIMITER " "

// Server responses

#define CLIENT_ALREADY_LOGGED_IN 200
#define BAD_USERNAME_PASSWORD 201
#define LOGIN_SUCCEEDED 202
#define REGISTER_FAILURE 203
#define REGISTER_SUCCEEDED 204
#define USERNAME_EXISTS 205
#define NOT_LOGGED_IN 206
#define USER_ALREADY_LOGGED_IN 207

#define CONNECT_SUCCESS 420
#define DISCONNECT_SUCCESS 421
#define OPEN_CHAT_ROOM_SUCCESS 440
#define ROOM_NAME_EXISTS 441
#define JOIN_ROOM_SUCCESS 460
#define ROOM_DOES_NOT_EXIST 461

#define EXIT_ROOM_SUCCESS 480
#define NOT_IN_SESSION_OR_ROOM 481
#define CLOSE_SESSION_SUCCESS 490

#define CLOSE_ROOM_SUCCESS 500
#define NOT_ROOM_OWNER 501

#define USER_NOT_FOUND 522
#define OTHER_USER_BUSY 523
#define SESSION_WITH_SELF 524

#define STATUS_FREE 540
#define STATUS_IN_A_ROOM 541
#define STATUS_IN_A_SESSION 542

#define SOMEONE_JOINED_CHAT_ROOM 560
#define SOMEONE_LEFT_CHAT_ROOM   561
#define ROOM_WAS_CLOSED          562

#define ALREADY_BUSY 462

#define EXPECTED_COMMAND_BYTES_SIZE 				 4
#define EXPECTED_MESSAGE_LENGTH_INDICATOR_BYTES_SIZE 4

#define DONE_SENDING_ROOM_PARTICIPANTS "DONE_SENDING_ROOM_PARTICIPANTS"
#define TEST_PEER_NAME "test"
#define SESSION_REFUSED_MSG "Connection to peer refused, peer might be busy or disconnected, try again later"



#endif /* TCPMESSENGERPROTOCOL_H_ */
