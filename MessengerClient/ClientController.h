/*
 * ClientController.h
 *
 *  Created on: Feb 27, 2017
 *      Author: user
 */

#ifndef CLIENTCONTROLLER_H_
#define CLIENTCONTROLLER_H_

#include "string"

using namespace std;

class ClientController
{
	public:
		ClientController();
		bool login(string username, string password);
		bool registerUser(string username, string password);
};

#endif /* CLIENTCONTROLLER_H_ */
