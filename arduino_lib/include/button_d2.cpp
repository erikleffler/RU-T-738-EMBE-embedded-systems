#include "button_d2.h"

void ButtonD2::init() {

	// Configure PD2 as an input using the Data Direction Register D
    DDRD &= ~_BV(DDD2);

    // Enable the pull-up resistor on PD2 using the Port D Data Register
    PORTD |= _BV(PORTD2);

	// Enable pin change interrupt on the PCINT18 pin using Pin Change Mask Register 2
	PCMSK2 |= _BV(PCINT18);

	// Enable pin change interrupt 2 using the Pin Change Interrrupt Control Register 
	PCICR |= _BV(PCIE2);
}

bool ButtonD2::is_pressed() {
	return (PIND & _BV(PIND2));
}

bool ButtonD2::debounced() {
	return (PIND & _BV(PIND2));
}
