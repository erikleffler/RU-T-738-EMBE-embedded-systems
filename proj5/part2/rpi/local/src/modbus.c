#include "modbus.h"

#define HIGHER_8(x) (x >> (8 * sizeof(x) - 8))
#define LOWER_8(x) (x & 0xff)

uint8_t readHoldingRegister(char* response_buffer, uint8_t fd, uint8_t address,
                            uint16_t first_register, uint16_t register_count) {


	char packet[6] = {
		(char) address,
		'\x03',
		(char) HIGHER_8(first_register),
		(char) LOWER_8(first_register),
		(char) HIGHER_8(register_count),
		(char) LOWER_8(register_count)
	};

	if (write(fd, packet, sizeof(packet)) != sizeof(packet)) {
		perror("Failed to write read holding register packet\n");
		return -1;
	}
	return 0;
}
