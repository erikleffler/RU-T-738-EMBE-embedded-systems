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

#define S_(x) #x
#define S(x) S_(x)

#define COMMAND_REGISTER 0

#define BUFFER_SIZE 20

typedef enum command {
    set_operational = 0x01,
    stop = 0x02,
    set_pre_operational = 0x80,
    reset = 0x81,
    reset_communications = 0x82
} command_t;

typedef enum state {
    initialization,
    pre_operational,
    operational,
    stopped,
} state_t;

int main(int argc, char *argv[]) {
    int fd, device;
    state_t device_states[2] = {initialization, initialization};
    state_t new_state;
    command_t command;
    char input[BUFFER_SIZE] = {0};
    struct termios options;

    if ((fd = open("/dev/ttyS0", O_RDWR | O_NOCTTY)) < 0) {
        perror("UART: Failed to open the fd.\n");
        return -1;
    }

    tcgetattr(fd, &options);

    options.c_cflag = B115200 | CS8 | CREAD | CLOCAL;
    options.c_iflag = IGNPAR | ICRNL;
    cfmakeraw(&options);

    tcflush(fd, TCIFLUSH);
    tcsetattr(fd, TCSANOW, &options);

    while (1) {
        // Read input that specifies command

        scanf("d %d c %" S(BUFFER_SIZE) "s", &device, input);

		// Ghetto stdin reset required for scanf. 
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
        }

        printf("Sending command %d to device %d\n", command, device);

        if (!(device == 1 || device == 2)) {
            printf("Bad device %d, only 1 or 2 available\n", device);
            continue;
        }

        if (strcmp(input, "set_pre_operational") == 0) {
            command = set_pre_operational;
            new_state = pre_operational;

        } else if (strcmp(input, "set_operational") == 0) {
            command = set_operational;
            new_state = operational;

        } else if (strcmp(input, "stop") == 0) {
            command = stop;
            new_state = stopped;

        } else if (strcmp(input, "reset") == 0) {
            command = reset;
            new_state = initialization;

        } else if (strcmp(input, "reset_communications") == 0) {
            command = reset_communications;
            new_state = initialization;

        } else {
            printf("Bad command\n");
            continue;
        }

        // Send command

        if (writeSingleRegister(fd, device, COMMAND_REGISTER, command) != 0) {
            printf("Failed sending commad %d to device %d\n", command, device);
            continue;
        }

        device_states[device - 1] = new_state;
    }

    close(fd);

    return 0;
}
