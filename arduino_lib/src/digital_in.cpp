#include "digital_in.h"

DigitalIn::DigitalIn(uint8_t pin_n) : pin_mask(1 << pin_n) {
	
}

DigitalIn::DigitalIn() {
	
}

void DigitalIn::init() {
	DDRB &= ~pin_mask;
	PORTB |= pin_mask;
}

bool DigitalIn::read() {
	return PINB & pin_mask;
}
