#include "digital_out.h"

DigitalOut::DigitalOut(uint8_t pin_n) : pin_mask(1 << pin_n) {
	
}

DigitalOut::DigitalOut() {
	
}

void DigitalOut::init() {
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
