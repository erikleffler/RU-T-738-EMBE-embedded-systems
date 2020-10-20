#ifndef READ_TASK
#define READ_TASK

#include <pthread.h>
#include <stdio.h>

#include "fifo.h"

void *readTask(void *param);

#endif // READ_TASK
