/*
 * CommandUtils.cpp
 *
 *  Created on: Mar 1, 2017
 *      Author: user
 */

#include "CommandUtils.h"

CommandUtils::CommandUtils() {}
CommandUtils::~CommandUtils() {}

/**
 * This function receives a command line and determines if the command (disreguarding the arguments) is the prefix
 */
bool CommandUtils::doesCommandHavePrefix(string command, string prefix)
{
	if (command.length() <= prefix.length())
	{
		return false;
	}

	// Get the index of the first space
	int firstSpaceIndex = command.find_first_of(' ', 0);

	// Check if the substring until the first space equals the prefix
	return command.substr(0, firstSpaceIndex).compare(prefix) == 0;
}

/**
 * This function receives a command line and returns its arguments.
 */
vector<string> CommandUtils::getCommandArgs(string command, string prefix)
{
	vector<string> args;

	// Cut the command itself, and stay only with the args
	string argsString = command.substr(prefix.length()+1, command.length());

	for (int i=0; i<argsString.length(); i++)
	{
		int start = i;

		char currChar = argsString.at(i);

		// Keep going until we reach the end or a space
		while (currChar != ' ' && i+1 < argsString.length())
		{
			i++;
			currChar = argsString.at(i);
		}

		// If this is the last arg
		if (i+1 >= argsString.length())
		{
			i++;
		}

		// Add the current arg to the list
		args.push_back(argsString.substr(start, i));
	}

	return args;
}

