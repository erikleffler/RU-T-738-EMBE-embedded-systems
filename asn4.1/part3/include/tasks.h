#ifndef TASKS_H
#define TASKS_H

#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

#include "fifo.h"

extern pthread_mutex_t sharedVariableMutex;
extern Fifo gSharedFifo;

void*decrementTask(void*param);
void*incrementTask(void*param);

#endif
