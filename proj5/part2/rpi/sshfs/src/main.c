#include <fcntl.h>
#include <getopt.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#include "modbus.h"

#define MAKE_16(higher, lower) (((uint16_t)higher << 8) | (uint16_t)lower)

int main(int argc, char *argv[]) {
    int fd;
    uint8_t device_address;
    uint16_t value;  // Value to write in case command is write
    char command, opt;
    char response_buffer[2];  // Only for response from read - 2 bytes since we
                              // just read one register

    // #### PARSE ARGS ####

    static struct option long_options[] = {
        {"command", required_argument, NULL, 'c'},
        {"device", required_argument, NULL, 'd'},
        {"value", optional_argument, NULL, 'v'},
        {NULL, 0, NULL, 0}};

    int option_index = 0;

    opt = getopt_long(argc, argv, "abc:d:f:", long_options, &option_index);

    /* Detect the end of the options. */
    if (opt == -1) return -1;

    switch (opt) {
        case 0:
            /* If this option set a flag, do nothing else now. */
            if (long_options[option_index].flag != 0) break;
            printf("option %s", long_options[option_index].name);
            if (optarg) printf(" with arg %s", optarg);
            printf("\n");
            break;

        case 'c':
            command = optarg[0];  // Just need first character to differentiate
                                  // [R]ead from [W]rite
            break;

        case 'd':
            device_address = atoi(optarg);
            break;

        case 'v':
            value = atoi(optarg);
            break;
        default:
            abort();
    }

    // #### DONE WITH PARSE ####

    if ((fd = open("/dev/ttyS0", O_RDWR | O_NOCTTY | O_NDELAY)) < 0) {
        perror("UART: Failed to open the fd.\n");
        return -1;
    }

    struct termios options;

    tcgetattr(fd, &options);

    options.c_cflag = B115200 | CS8 | CREAD | CLOCAL;
    options.c_iflag = IGNPAR | ICRNL;
    cfmakeraw(&options);

    tcflush(fd, TCIFLUSH);
    tcsetattr(fd, TCSANOW, &options);

    switch (command) {
        case 'r':
            readHoldingRegisters(response_buffer, fd, device_address, 0x01,
                                 0x01);
            printf("Read %04x\n",
                   MAKE_16(response_buffer[0], response_buffer[1]));
        case 'w':
            writeSingleRegister(fd, device_address, 0x01, value);
    }

    return 0;
}
