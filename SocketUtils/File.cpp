/*
 * File.cpp
 *
 *  Created on: Dec 30, 2016
 *      Author: user
 */

#include "File.h"
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace npl;


File::File(const string path) {
	myFile.open(path.c_str(), ios::in | ios::out | ios::binary);
}

void File::close() {
	myFile.close();
}

int File::read(char buff[], int size) {
	// Check if the file is open before reading
	if (!myFile.is_open())
	{
		return -1;
	}

	myFile.read(buff, size);
	return 1;
}

int File::write(const char msg[], int size) {
	// Check if the file is open before writing
	if (!myFile.is_open())
	{
		return -1;
	}

	myFile.write(msg, size);
	return 1;
}

File::~File(){
	close();
}
