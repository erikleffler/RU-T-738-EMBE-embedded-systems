#ifndef TASKS_H
#define TASKS_H

#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

extern pthread_mutex_t sharedVariableMutex;
extern int gSharedVariable;

void*decrementTask(void*param);
void*incrementTask(void*param);

#endif
