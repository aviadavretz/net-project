/*
 * File.h
 *
 *  Created on: Dec 30, 2016
 *      Author: user
 */

#ifndef FILE_H_
#define FILE_H_

#include <fstream>

using namespace std;

namespace npl {


class File
{
private:
	fstream myFile;

public:
	File(const string path);
	void close();
	int read(char buff[], int size);
	int write(const char msg[], int size);

	~File();
};

}
#endif /* SOCKET_H_ */
