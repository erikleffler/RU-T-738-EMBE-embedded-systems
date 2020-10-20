#ifndef READ_TASK
#define READ_TASK

#include <pthread.h>
#include <stdio.h>

#include <poll.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_LINE_SZ 50

void *transmitTask(void *param);
void *receiveTask(void *param);

#endif // READ_TASK
