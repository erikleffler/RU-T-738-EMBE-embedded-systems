#include "tasks.h"

#define HIGHER_8(x) (x >> (8 * sizeof(x) - 8))
#define LOWER_8(x) (x & 0xff)
#define REV_ENDIAN_16(x) ((LOWER_8((uint16_t)x) << 8) | (HIGHER_8((uint16_t)x)))

#define ANALOG_OUT_REGISTER 2
#define ANALOG_IN_REGISTER 3

void *readAnalogTask(void *arg) {
    serial_thread_data_t *thread_data = (serial_thread_data_t *)arg;

    uint16_t *analog_val = thread_data->analog_val;
    uint8_t device_address = thread_data->device_address;
    int fd = thread_data->fd;
    uint8_t exit_request = thread_data->exit_request;

    while (1) {
        pthread_mutex_lock(&serial_mutex);

        readHoldingRegisters((char *)analog_val, 2, fd, device_address,
                             ANALOG_IN_REGISTER, 1);

		*analog_val = REV_ENDIAN_16(*analog_val);

        pthread_mutex_unlock(&serial_mutex);

        if (exit_request) {
            pthread_exit(NULL);
        }
    }
}

void *writeAnalogTask(void *arg) {
    serial_thread_data_t *thread_data = (serial_thread_data_t *)arg;

    uint16_t *analog_val = thread_data->analog_val;
    uint8_t device_address = thread_data->device_address;
    int fd = thread_data->fd;
    uint8_t exit_request = thread_data->exit_request;

    while (1) {
        pthread_mutex_lock(&serial_mutex);

        writeSingleRegister(fd, device_address, ANALOG_OUT_REGISTER,
                            *analog_val);

        pthread_mutex_unlock(&serial_mutex);

        if (exit_request) {
            pthread_exit(NULL);
        }
    }
}
