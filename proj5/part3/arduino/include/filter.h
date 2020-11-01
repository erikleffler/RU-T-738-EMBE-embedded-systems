#pragma once
#include <Arduino.h>

class Filter
{
    public:
        void init();
        int smooth(int value);

    private:
        int numReadings;
        int readings[10];             // the readings from the analog input
        int readIndex;              // the index of the current reading
        int total;                  // the running total
        int average;                // the average

};