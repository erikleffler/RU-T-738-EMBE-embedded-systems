#pragma once
#include <Arduino.h>

class Analog_in
{
    public:
        Analog_in(int pin);
        void init();
        int read();

    private:
        uint8_t pinMask;
        int Pin;
        int photocellReading;     // the analog reading from the sensor divider
        int LEDbrightness;
};