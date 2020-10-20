#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <termios.h>  // using the termios.h library
#include <unistd.h>

#include "fifo.h"
#include "read_task.h"

#define INPUT_SZ 50

pthread_t read_task_obj;
pthread_mutex_t char_fifo_mutex;
CharFifo char_fifo;

int main() {
    int file;
    if ((file = open("/dev/ttyS0", O_RDWR | O_NOCTTY | O_NDELAY)) < 0) {
        perror("UART: Failed to open the file.\n");
        return -1;
    }

    struct termios options;     // the termios structure is vital
    tcgetattr(file, &options);  // sets the parameters for the file

    // Set up the communications options:
    // 115200 baud, 8-bit, enable receiver, no modem control lines
    options.c_cflag = B115200 | CS8 | CREAD | CLOCAL;
    options.c_iflag = IGNPAR | ICRNL;    // ignore partity errors
    tcflush(file, TCIFLUSH);             // discard file information
    tcsetattr(file, TCSANOW, &options);  // changes occur immmediately

    // Init the char fifo and start task to read from stdin
    initCharFifo(&char_fifo, INPUT_SZ);
    pthread_mutex_init(&char_fifo_mutex, NULL);
    pthread_create(&read_task_obj, NULL, readTask, NULL);

    unsigned char receive[INPUT_SZ];

    unsigned char transmit[INPUT_SZ];
    unsigned char *p = transmit;

    int count;

    while (1) {
        // Get input from stdin if it exists
        pthread_mutex_lock(&char_fifo_mutex);

        // Copy fifo bytes into local buffer
        while (!charFifoIsEmpty(&char_fifo)) {
            *p++ = readFromCharFifo(&char_fifo);
        }

        pthread_mutex_lock(&char_fifo_mutex);

        ptrdiff_t n_read = p - transmit;

        // Write local buffer over uart
        if ((count = write(file, &transmit, n_read)) < 0) {  // transmit
            perror("Failed to write to the output\n");
            return -1;
        }

        // Reset p
        p = transmit;

        // Recieve from uart

        if ((count = read(file, (void *)receive, INPUT_SZ)) <
            0) {  // receive data
            perror("Failed to read from the input\n");
            return -1;
        }
        if (count > 0) printf("%s", receive);
    }

    close(file);

    pthread_join(read_task_obj, NULL);

    return 0;
}
