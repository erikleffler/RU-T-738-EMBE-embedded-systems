#include "modbus.h"

#define HIGHER_8(x) (x >> (8 * sizeof(x) - 8))
#define LOWER_8(x) (x & 0xff)
#define MAKE_16(higher, lower) (((uint16_t)higher << 8) | (uint16_t)lower)

uint8_t readHoldingRegisters(char* response_buffer, uint8_t fd, uint8_t address,
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

    if (read(fd, &return_code, 1) != 1) {
        perror("Failed to read return code from received  packet\n");
        return -1;
    }

    // ERROR
    if (return_code == '\x83') {
        return handleExceptionCode(fd, first_register, register_count);

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

uint8_t writeSingleRegister(uint8_t fd, uint8_t address,
                            uint16_t register_address, uint16_t value) {
    char return_code;

    char packet[6] = {(char)address,
                      '\x06',
                      (char)HIGHER_8(register_address),
                      (char)LOWER_8(register_address),
                      (char)HIGHER_8(value),
                      (char)LOWER_8(value)};

    if (write(fd, packet, sizeof(packet)) != sizeof(packet)) {
        perror("Failed to write write single register packet\n");
        return -1;
    }

    usleep(1000000);

    if (read(fd, &return_code, 1) != 1) {
        perror("Failed to read return code from received packet\n");
        return -1;
    }

    // ERROR
    if (return_code == '\x86') {
        return handleExceptionCode(fd, register_address, value);

    } else if (return_code == '\x06') {  // Success

        char word_buff[2];

        if (read(fd, &word_buff, 2) != 2) {
            perror("Failed to read register address from received  packet\n");
            return -1;
        }

        if (MAKE_16(word_buff[0], word_buff[1]) != register_address) {
            fprintf(stderr,
                    "Recieved unexpected address after writeSingleRegister, "
                    "received: %04x, expected: %04x\n",
                    MAKE_16(word_buff[0], word_buff[1]), register_address);
            return 1;
        }

        if (read(fd, &word_buff, 2) != 2) {
            perror("Failed to read register address from received  packet\n");
            return -1;
        }

        if (MAKE_16(word_buff[0], word_buff[1]) != value) {
            fprintf(stderr,
                    "Recieved unexpected value after writeSingleRegister, "
                    "received: %04x, expected: %04x\n",
                    MAKE_16(word_buff[0], word_buff[1]), value);
            return 1;
        }

        return 0;
    }

    fprintf(stderr, "Error: unexpected return code %d\n", return_code);
    return 1;
}

uint8_t handleExceptionCode(uint8_t fd, uint16_t first_argument,
                            uint16_t second_argument) {
    uint8_t exception_code;

    if (read(fd, &exception_code, 1) != 1) {
        perror("Failed to read return code from received  packet\n");
        return -1;
    }

    switch (exception_code) {
        case 1:
            fprintf(stderr, "Recieved error illegal function\n");
            return 1;
        case 2:
            fprintf(stderr,
                    "Recieved error illegal data address for first "
                    "register %04x and register count %04x\n",
                    first_argument, second_argument);
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
}
