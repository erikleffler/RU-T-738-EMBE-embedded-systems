#include <fcntl.h>
#include <getopt.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#include "modbus.h"
#include "tasks.h"

#define MAKE_16(higher, lower) (((uint16_t)higher << 8) | (uint16_t)lower)
#define HIGHER_8(x) (x >> (8 * sizeof(x) - 8))
#define LOWER_8(x) (x & 0xff)
#define REV_ENDIAN_16(x) ((LOWER_8((uint16_t)x) << 8) | (HIGHER_8((uint16_t)x)))

#define S_(x) #x
#define S(x) S_(x)

#define COMMAND_REGISTER 0
#define PRE_OP_CONF_REGISTER 1
#define ANALOG_OUT_REGISTER 2
#define ANALOG_IN_REGISTER 3
#define STATE_REGISTER 4

#define BUFFER_SIZE 20

typedef enum command {
    set_operational = 0x01,
    stop = 0x02,
    set_pre_operational = 0x80,
    reset = 0x81,
    reset_communications = 0x82
} command_t;

typedef enum state {
    initialization = 0,
    pre_operational = 1,
    operational = 2,
    stopped = 3,
} state_t;

typedef enum pre_operational_config {
    read_analog = 0,
    write_analog = 1,
    low = 2,
    high = 3,
    ambient = 4,
} pre_operational_config_t;

int main(int argc, char *argv[]) {
    int fd;
    uint16_t register_value, analog_value;

    state_t device_states[2] = {initialization, initialization};
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
        // Ensure both devices are pre-operational
        while (device_states[0] != pre_operational ||
               device_states[1] != pre_operational) {
            readHoldingRegisters((char *)&register_value, 2, fd, 1,
                                 STATE_REGISTER, 1);
            device_states[0] = (state_t)REV_ENDIAN_16((state_t)register_value);

            readHoldingRegisters((char *)&register_value, 2, fd, 2,
                                 STATE_REGISTER, 1);
            device_states[1] = (state_t)REV_ENDIAN_16((state_t)register_value);

            printf("Device 1 state: %d\n", device_states[0]);
            printf("Device 2 state: %d\n", device_states[1]);
        }

        printf("Both devices in pre-op mode, sending config packets.\n");

        // Configure device 1 to be in read mode and ambient mode
        uint16_t pre_op_config = (1 << read_analog) | (1 << ambient);
        writeSingleRegister(fd, 1, PRE_OP_CONF_REGISTER, pre_op_config);

        // Configure device 2 to be in write mode and ambient mode
        pre_op_config = (1 << write_analog) | (1 << ambient);
        writeSingleRegister(fd, 2, PRE_OP_CONF_REGISTER, pre_op_config);

        printf("Finished configuring, setting both devices to operational.\n");

        // Set both devices to operational mode
        writeSingleRegister(fd, 1, COMMAND_REGISTER, set_operational);
        writeSingleRegister(fd, 2, COMMAND_REGISTER, set_operational);

        // Ensure both devices are operational
        while (device_states[0] != operational ||
               device_states[1] != operational) {
            readHoldingRegisters((char *)&register_value, 2, fd, 1,
                                 STATE_REGISTER, 1);
            device_states[0] = (state_t)REV_ENDIAN_16((state_t)register_value);

            readHoldingRegisters((char *)&register_value, 2, fd, 2,
                                 STATE_REGISTER, 1);
            device_states[1] = (state_t)REV_ENDIAN_16((state_t)register_value);

            printf("Device 1 state: %d\n", device_states[0]);
            printf("Device 2 state: %d\n", device_states[1]);
        }

        printf(
            "Both devices in operational-op mode, starting control tasks.\n");

        while (1) {
            readHoldingRegisters((char *) &analog_value, 2, fd, 1,
                                 ANALOG_IN_REGISTER, 1);

			analog_value = REV_ENDIAN_16(analog_value);

            writeSingleRegister(fd, 2, ANALOG_OUT_REGISTER, analog_value);
        }
    }

    close(fd);

    return 0;
}
