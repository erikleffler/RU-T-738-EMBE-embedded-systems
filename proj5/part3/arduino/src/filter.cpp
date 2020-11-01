#include <filter.h>

void Filter::init() {
    numReadings = 10;
    readIndex = 0;
    total = 0;
    average = 0;
    for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[ thisReading ] = 0;
  }
}

int Filter::smooth(int value) {
    // subtract the last reading:
    total = total - readings[readIndex];
    // read from the sensor:
    readings[readIndex] = value;
    // add the reading to the total:
    total = total + readings[readIndex];
    // advance to the next position in the array:
    readIndex = readIndex + 1;

    // if we're at the end of the array...
    if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
    }
    // calculate the average:
    average = total / numReadings;
    // send it to the computer as ASCII digits
    //Serial.println( average, DEC);
    delay(5);

    return average;
}