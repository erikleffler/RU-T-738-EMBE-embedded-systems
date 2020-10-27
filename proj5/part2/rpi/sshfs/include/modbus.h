#ifndef _MODBUS_H_
#define _MODBUS_H_

#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

uint8_t readHoldingRegister(char* response_buffer, uint8_t fd, uint8_t address,
                            uint16_t first_register, uint16_t register_count);

#endif  // _MODBUS_H_
