#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <termios.h>  // using the termios.h library
#include <unistd.h>

#include "uart_tasks.h"

pthread_t transmit_task_obj;
pthread_t receive_task_obj;
int file;

int main() {
    if ((file = open("/dev/ttyS0", O_RDWR | O_NOCTTY | O_NDELAY)) < 0) {
        perror("UART: Failed to open the file.\n");
        return -1;
    }

    struct termios options;     // the termios structure is vital
    tcgetattr(file, &options);  // sets the parameters for the file

    // Set up the communications options:
    // 115200 baud, 8-bit, enable receiver, no modem control lines
    options.c_cflag = B115200 | CS8 | CREAD | CLOCAL;
    options.c_iflag = IGNPAR | ICRNL;  // ignore partity errors

    tcflush(file, TCIFLUSH);             // discard file information
    tcsetattr(file, TCSANOW, &options);  // changes occur immmediately

    usleep(100000);

    pthread_create(&transmit_task_obj, NULL, transmitTask, NULL);
    pthread_create(&receive_task_obj, NULL, receiveTask, NULL);

    pthread_join(transmit_task_obj, NULL);
    pthread_join(receive_task_obj, NULL);
}
