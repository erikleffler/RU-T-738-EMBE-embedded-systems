#include <analog_in.h>

Analog_in::Analog_in(int pin) {
    pinMask = (1 << pin);
    this->Pin = pin;
}

// Set chosen pin to input
void Analog_in::init() {
    DDRC &= ~pinMask;
	//pinMode(Pin, INPUT);
}

int Analog_in::read() {
    // read input from the chosen pin
    photocellReading = analogRead(this->Pin);
   
    // LED gets brighter the darker it is at the sensor
    // that means we have to -invert- the reading from 0-1023 back to 1023-0
    photocellReading = 1023 - photocellReading;

    //now we have to map 0-1023 to 0-255 since thats the range analogWrite uses
    LEDbrightness = map(photocellReading, 0, 1023, 0, 255);

    return LEDbrightness;
}