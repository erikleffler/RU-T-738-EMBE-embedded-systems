#include "digital_in.h"

void DigitalIn::init(uint8_t pin) {
	this->pin_mask = (1 << pin);
	DDRB &= ~this->pin_mask;
	PORTB |= this->pin_mask;
}

bool DigitalIn::read() {
	return PINB & this->pin_mask;
}
