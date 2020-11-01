#pragma once
#include <Arduino.h>

#define TIME 500

class Analog_out
{
    public:
        Analog_out(int pin);
        void init();
        void set_hi();
        void set_lo();
        void toggle();
        void set_val(uint8_t value);

    private:
        uint8_t pinMask;
        bool is_low;
        uint8_t pin;
};