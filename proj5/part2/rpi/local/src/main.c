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

    opt = getopt_long(argc, argv, "c:d:v:", long_options, &option_index);
    while (opt != 0xff) {
        switch (opt) {
            case 'c':
                command = optarg[0];  // Just need first character to
                                      // differentiate [R]ead from [W]rite
                printf("Command: %c\n", command);
                break;

            case 'd':
                device_address = atoi(optarg);
                printf("Device address: %d\n", device_address);
                break;

            case 'v':
                value = atoi(optarg);
                printf("Value: %d\n", value);
                break;

            default:
                printf("unknown argument %02x\n", opt);
                return -1;
        }
        opt = getopt_long(argc, argv, "c:d:v:", long_options, &option_index);
    }

    // #### DONE WITH PARSE ####

    if ((fd = open("/dev/ttyS0", O_RDWR | O_NOCTTY)) < 0) {
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

        default:
            printf("Unknown command %c\n", opt);
            return -1;
    }

    close(fd);

    return 0;
}
