#include "uart_tasks.h"

extern int file;

void *transmitTask(void *param) {
    printf("started transmit task\n");

    char c;
    int count, rv;

    char *buffer = (char *)malloc(MAX_LINE_SZ);

	// For poll
    struct pollfd transmit_poll;
    transmit_poll.fd = file;
    transmit_poll.events = POLLOUT;

	// Only needed for geline that requires a pointer to an int
    size_t sz = MAX_LINE_SZ;

    while (1) {
        count = getline(&buffer, &sz, stdin);
        if (count < 0) {
            perror("An error occurred when reading line from stdin");
        }

        rv = poll(&transmit_poll, 1, -1);

        if (rv == -1) {
            printf("An error occured during select() in transmitTask\n");
        }

        count = write(file, buffer, count);
        if (count < 0) {
            perror("Failed to write to the output\n");
        }
        memset(&buffer, 0, count);
    }
}

void *receiveTask(void *param) {
    printf("started receive task\n");

    char c;
    int count, rv;
    char buffer[MAX_LINE_SZ] = {0};

	// For poll
    struct pollfd receive_poll;
    receive_poll.fd = file;
    receive_poll.events = POLLIN;

    while (1) {
        rv = poll(&receive_poll, 1, -1);
        if (rv == -1) {
            printf("An error occured during select() in receiveTask\n");
        }

        count = read(file, &buffer, sizeof(buffer));
        if (count < 0) {
            perror("Failed to read the input\n");
        }

        if (count > 0) {
            printf("Recieved count: %d  bytes over UART: %s\n", count, buffer);
            memset(&buffer, 0, count);
        }
    }
}
