/* Simple send and receive C example for communicating with the
 *  Arduino echo program using /dev/ttyAMA0. Written by Derek Molloy
 *  (www.derekmolloy.ie) for the book Exploring Raspberry Pi. */

#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int file, count;

    if (argc != 2) {
        printf("Invalid number of arguments, exiting!\n");
        return -2;
    }

    char packet[3] = {'\x42', (uint8_t)atoi(argv[1]), '\x42'};

    if ((file = open("/dev/ttyS0", O_RDWR | O_NOCTTY | O_NDELAY)) < 0) {
        perror("UART: Failed to open the file.\n");
        return -1;
    }

    struct termios options;

    tcgetattr(file, &options);

    options.c_cflag = B115200 | CS8 | CREAD | CLOCAL;
    options.c_iflag = IGNPAR | ICRNL;
    cfmakeraw(&options);

    tcflush(file, TCIFLUSH);
    tcsetattr(file, TCSANOW, &options);

    if ((count = write(file, packet, sizeof(packet)) < 0)) {
        perror("Failed to write to the output\n");
        return -1;
    }

    usleep(100000);

    unsigned char receive[100];

    if ((count = read(file, (void *)receive, 100)) < 0) {
        perror("Failed to read from the input\n");
        return -1;
    }

    if (count == 0)
        printf("There was no data available to read!\n");
    else {
        receive[count] = 0;  // There is no null character sent by the Arduino
        printf("The following was read in [%d]: %s\n", count, receive);
    }

    close(file);
    return 0;
}
