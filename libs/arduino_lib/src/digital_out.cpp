#include "digital_out.h"

void DigitalOut::init(uint8_t pin) {
	this->pin_mask = (1 << pin);
	DDRB |= pin_mask;
}

void DigitalOut::set_hi() {
	PORTB |= pin_mask;
}

void DigitalOut::set_lo() {
	PORTB &= ~pin_mask;
}

void DigitalOut::toggle() {
	PORTB ^= pin_mask;
}
