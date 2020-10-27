#include "modbus.h"

#define HIGHER_8(x) (x >> (8 * sizeof(x) - 8))
#define LOWER_8(x) (x & 0xff)

uint8_t readHoldingRegister(char* response_buffer, uint8_t fd, uint8_t address,
                            uint16_t first_register, uint16_t register_count) {
    char return_code;

    char packet[6] = {(char)address,
                      '\x03',
                      (char)HIGHER_8(first_register),
                      (char)LOWER_8(first_register),
                      (char)HIGHER_8(register_count),
                      (char)LOWER_8(register_count)};

    if (write(fd, packet, sizeof(packet)) != sizeof(packet)) {
        perror("Failed to write read holding register packet\n");
        return -1;
    }

    usleep(1000000);

    if (read(fd, &return_code, 1) != 1) {
        perror("Failed to read return code from received  packet\n");
        return -1;
    }

    // ERROR
    if (return_code == '\x83') {
        uint8_t exception_code;

        if (read(fd, &exception_code, 1) != 1) {
            perror("Failed to read return code from received  packet\n");
            return -1;
        }

        close(fd);

        switch (exception_code) {
            case 1:
                fprintf(stderr, "Recieved error illegal function\n");
                return 1;
            case 2:
                fprintf(stderr,
                        "Recieved error illegal data address for first "
                        "register %04x and register count %04x\n",
                        first_register, register_count);
                return 1;
            case 3:
                fprintf(stderr, "Recieved error illegal data value\n");
                return 1;
            case 4:
                fprintf(stderr, "Recieved error slave device failure\n");
                return 1;
        }
        fprintf(stderr, "Recieved unknown error\n");
        return 1;
    } else if (return_code == '\x03') {  // Success

        uint8_t n_bytes;

        if (read(fd, &n_bytes, 1) != 1) {
            perror("Failed to read number of bytes from received  packet\n");
            return -1;
        }

        if (read(fd, response_buffer, n_bytes) != n_bytes) {
            perror("Failed to read bytes in packet packet\n");
            return -1;
        }

        return 0;
    }

    fprintf(stderr, "Error: unexpected return code %d\n", return_code);
    return 1;
}
