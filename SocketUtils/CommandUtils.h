/*
 * CommandUtils.h
 *
 *  Created on: Mar 1, 2017
 *      Author: user
 */

#ifndef COMMANDUTILS_H_
#define COMMANDUTILS_H_

#include "string"
#include <vector>

using namespace std;

class CommandUtils {
public:
	bool doesCommandHavePrefix(string command, string prefix);
	vector<string> getCommandArgs(string command, string prefix);
	string getCommandSingleArg(string command, string prefix);

	CommandUtils();
	virtual ~CommandUtils();
};

#endif /* COMMANDUTILS_H_ */
