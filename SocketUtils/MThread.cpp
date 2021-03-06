/*
 * Mthread.cpp
 *
 *  Created on: Feb 13, 2013
 *      Author: Eliav Menachi
 */

#include "MThread.h"
#include <iostream>
#include <stdio.h>
using namespace std;
using namespace npl;

void* worker(void* arg){
	MThread* threadObj = (MThread*)arg;
	threadObj->run();
	threadObj->threadId = 0;
	return NULL;
}

void MThread::start(){
	// Create a thread, and send this Mthread instance as the arg to the startRoutine.
	pthread_create(&threadId,NULL,worker,(void*)this);
}

void MThread::waitForThread(){
	pthread_join(threadId,NULL);
	threadId=0;
}

MThread::~MThread(){
	if (threadId>0){
		// Kills the thread if it exists
		pthread_cancel(threadId);
		cout << "Thread stopped." << endl;
	}
}

