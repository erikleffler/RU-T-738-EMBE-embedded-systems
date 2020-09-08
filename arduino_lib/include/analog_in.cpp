#include "analog_in.h"

void AnalogIn::init(uint8_t pin) {
	this->pin = pin;
	pinMode(pin, INPUT);
}

uint8_t AnalogIn::read() {
	return analogRead(this->pin) >> 2;
}

