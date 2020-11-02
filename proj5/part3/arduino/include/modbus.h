#pragma once
#include <Arduino.h>
#include <stdint.h>
#include <context.h>

#ifndef MODBUS_ADDRESS
#define MODBUS_ADDRESS -1
#endif
#define MSG_LEN 8

#define HIGHER_8(x) (x >> (8 * sizeof(x) - 8))
#define LOWER_8(x) (x & 0xff)
#define MAKE_16(higher, lower) (((uint16_t)higher << 8) | (uint16_t)lower)

class Modbus
{
    public:
        Modbus();
        uint16_t ModRTU_CRC(uint8_t buf[], int len);
        bool handle_crc(uint8_t msg[]);
        void setCrc(uint8_t* packet, size_t length);
        uint8_t verifyCrc(char* packet, size_t length);
        uint8_t handle_read(uint8_t msg[]);
        uint8_t handle_write(uint8_t msg[]);
        uint8_t handle_input();
        void get_context(Context *context);

        uint8_t ledPin;
        uint8_t led_val;
        Context *context_ptr;

    private:
};