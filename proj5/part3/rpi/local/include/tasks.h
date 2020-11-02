#ifndef _TASKS_H_
#define _TASKS_H_

#include <pthread.h>

#include "modbus.h"

typedef struct serial_thread_data_t {
    uint16_t *analog_val;
    uint8_t device_address;
    int fd;
    uint8_t exit_request;
} serial_thread_data_t;

extern pthread_mutex_t serial_mutex;

void *writeAnalogTask(void *arg);
void *readAnalogTask(void *arg);

#endif  // _TASKS_H_
