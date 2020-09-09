#include "digital_out.h"

void DigitalOut::init(uint8_t pin) {
	this->pin_mask = (1 << pin);
	DDRB |= this->pin_mask;
}

void DigitalOut::set_hi() {
	PORTB |= this->pin_mask;
}

void DigitalOut::set_lo() {
	PORTB &= ~this->pin_mask;
}

void DigitalOut::toggle() {
	PORTB ^= this->pin_mask;
}
