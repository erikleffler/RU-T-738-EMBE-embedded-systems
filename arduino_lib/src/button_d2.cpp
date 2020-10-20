#include "button_d2.h"

ButtonD2::ButtonD2() : recently_pressed(false) {}

void ButtonD2::init() {

	noInterrupts();

	// Configure PD2 as an input using the Data Direction Register D
    DDRD &= ~_BV(DDD2);

    // Enable the pull-up resistor on PD2 using the Port D Data Register
    PORTD |= _BV(PORTD2);

	// Enable pin change interrupt on the PCINT18 pin using Pin Change Mask Register 2
	PCMSK2 |= _BV(PCINT18);

	// Enable pin change interrupt 2 using the Pin Change Interrrupt Control Register 
	PCICR |= _BV(PCIE2);

	this->timer = Timer2();
	this->timer.init(64); // Think around 62hz is lowest possible freq for 8bit
	this->timer.disable();

	interrupts();

}

bool ButtonD2::is_pressed() {
	return (PIND & _BV(PIND2));
}

bool ButtonD2::bouncing() {

	this->timer.enable(); // Also resets timer if it's already enabled.

	if(this->recently_pressed) {
		return true;
	}

	this->recently_pressed = true;

	return false;
}

void ButtonD2::timer2_callback() {
	this->timer.disable();
	this->recently_pressed = false;
}
