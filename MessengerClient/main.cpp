#include <iostream>
#include "ClientController.h"

int main()
{
	int action;
	string username;
	string password;
	ClientController controller;

	cout << "Welcome! Please select: " << endl;
	cout << LOGIN << ") Login" << endl;
	cout << REGISTER << ") Register" << endl;
	cin >> action;

	cout << "Username: " << endl;
	cin >> username;
	cout << "Password: " << endl;
	cin >> password;

	bool success = false;

	switch (action)
	{
		case (LOGIN):
		{
			success = controller.login(username, password);

			if (!success)
			{
				cout << "Sorry, idiots are not allowed in." << endl;
			}

			break;
		}
		case (REGISTER):
		{
			success = controller.registerUser(username, password);

			if (!success)
			{
				cout << "You are too ugly to register." << endl;
			}

			break;
		}
	}

	return 0;
}
