/*
 * ServerRepliesListener.cpp
 *
 *  Created on: Mar 4, 2017
 *      Author: user
 */

#include "ServerRepliesListener.h"

ServerRepliesListener::ServerRepliesListener(ConnectionToServerManager* connection, ClientTerminalPrinter* printer, ServerRepliesObserver* observer)
{
	this->connection = connection;
	this->printer = printer;
	this->observer = observer;

	shouldContinue = true;
}

void ServerRepliesListener::run()
{
	while (shouldContinue)
	{
		int replyCode = connection->receiveReplyCode();

		switch (replyCode)
		{
		case (BAD_USERNAME_PASSWORD):
		{
			printer->print("Username or password is incorrect.");
			break;
		}
		case (CLIENT_ALREADY_LOGGED_IN):
		{
			printer->print("You are already logged in.");
			break;
		}
		case (USER_ALREADY_LOGGED_IN):
		{
			printer->print("The user you entered is already logged in.");
			break;
		}
		case (LOGIN_SUCCEEDED):
		{
			printer->print("Login successful!");
			break;
		}
		case (REGISTER_FAILURE):
		{
			printer->print("Registration failed, Please try again.");
			break;
		}
		case (USERNAME_EXISTS):
		{
			printer->print("The username you entered already exists.");
			break;
		}
		case (REGISTER_SUCCEEDED):
		{
			printer->print("Register successful!");
			break;
		}
		case (NOT_LOGGED_IN):
		{
			printer->print("Connected to " + connection->getAddr() + ", but not Logged-in.");
			break;
		}
		case (ALREADY_BUSY):
		{
			printer->print("You are already participating in a session or room.");
			break;
		}
		case (SESSION_WITH_SELF):
		{
			printer->print("You can't create a session with yourself!");
			break;
		}
		case (USER_NOT_FOUND):
		{
			printer->print("Requested user is either logged off or does not exist.");
			break;
		}
		case (OTHER_USER_BUSY):
		{
			printer->print("Requested user is busy.");
			break;
		}
		case (ROOM_NAME_EXISTS):
		{
			printer->print("Your requested room name is already taken.");
			break;
		}
		case (ROOM_DOES_NOT_EXIST):
		{
			printer->print("Requested room does not exist.");
			break;
		}
		case (NOT_IN_SESSION_OR_ROOM):
		{
			printer->print("You are not in a session or room.");
			break;
		}
		case (NOT_ROOM_OWNER):
		{
			printer->print("You are not the room owner.");
			break;
		}
		case (STATUS_FREE):
		{
			string addr = connection->getAddr();
			string username = connection->receiveMessage();

			printer->print("Connected to " + addr + ", Logged-in as " + username + ".");
			break;
		}
		case (STATUS_IN_A_ROOM):
		{
			string addr = connection->getAddr();
			string roomName = connection->receiveMessage();
			string username = connection->receiveMessage();

			printer->print("Connected to " + addr + ", Logged-in as " + username + ", in a ChatRoom named '" + roomName + "'.");
			break;
		}
		case (STATUS_IN_A_SESSION):
		{
			string addr = connection->getAddr();
			string otherUsername = connection->receiveMessage();
			string username = connection->receiveMessage();

			printer->print("Connected to " + addr + ", Logged-in as " + username + ", in a Session with " + otherUsername + ".");
			break;
		}
		case (SESSION_ESTABLISHED):
		{
			// TODO : Complete this
			observer->notifySessionEstablished();
			break;
		}
		case (OPEN_CHAT_ROOM_SUCCESS):
		{
			// TODO : Complete
			observer->notifyChatRoomOpened();
			break;
		}
		case (JOIN_ROOM_SUCCESS):
		{
			// TODO : Complete
			observer->notifyJoinedRoom();
			break;
		}
		case (EXIT_ROOM_SUCCESS):
		{
			// TODO : Complete
			observer->notifyExitRoom();
			break;
		}
		case (CLOSE_SESSION_SUCCESS):
		{
			// TODO: Complete
			observer->notifySessionClosed();
			break;
		}
		case (CLOSE_ROOM_SUCCESS):
		{
			// TODO: Complete
			observer->notifyRoomClosedSuccess();
			break;
		}
		case (DISCONNECT_SUCCESS):
		{
			observer->notifyDisconnected();
			break;
		}
		case (SOMEONE_JOINED_CHAT_ROOM):
		{
			observer->notifySomeoneJoinedRoom();
			break;
		}
		case (SOMEONE_LEFT_CHAT_ROOM):
		{
			observer->notifySomeoneLeftRoom();
			break;
		}
		case (ROOM_WAS_CLOSED):
		{
			observer->notifyRoomClosedByOwner();
			break;
		}
		case (GET_REGISTERED_USERS):
		{
			// Get the number of registered users first
			int usersNumber = atoi(connection->receiveMessage().c_str());

			if (usersNumber > 0)
			{
				printer->printRegisteredUsers(connection->receiveMessages(usersNumber));
			}
			else
			{
				printer->print("There are no registered users.");
			}

			break;
		}
		case (GET_CONNECTED_USERS):
		{
			// Get the number of registered users first
			int usersNumber = atoi(connection->receiveMessage().c_str());

			if (usersNumber > 0)
			{
				printer->printConnectedUsers(connection->receiveMessages(usersNumber));
			}
			else
			{
				printer->print("There are no connected users.");
			}

			break;
		}
		case (GET_CHAT_ROOMS):
		{
			// Get the number of rooms first
			int roomsNumber = atoi(connection->receiveMessage().c_str());

			if (roomsNumber > 0)
			{
				printer->printRooms(connection->receiveMessages(roomsNumber));
			}
			else
			{
				printer->print("There are no open chat-rooms.");
			}

			break;
		}
		case (GET_USERS_IN_CHAT_ROOM):
		{
			// Get the number of users in the room first
			int usersNumber = atoi(connection->receiveMessage().c_str());

			if (usersNumber > 0)
			{
				printer->printUsersInRoom(connection->receiveMessages(usersNumber));
			}
			else
			{
				printer->print("There are no users in the room.");
			}

			break;
		}
		default:
		{
			printer->printUnknownReplyCode(replyCode);
		}
		}
	}
}

void ServerRepliesListener::stop()
{
	shouldContinue = false;
}
