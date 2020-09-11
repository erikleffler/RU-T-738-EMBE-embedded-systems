#include <Arduino.h>
#include "../../arduino_lib/include/button_d2.h"
#include "../../arduino_lib/include/analog_out.h"
#include "../../arduino_lib/include/analog_in.h"

ButtonD2 button;
AnalogOut led;
AnalogIn input;

void setup() {

	Serial.begin(9600);
	// Timer setup

   	// LED setup
	led.init(5);

	// Photocell setup
	input.init(A0);

	// Button setup
	button.init();

}

void loop() {
	led.set_val(255 - input.read());
	Serial.println(input.read());
}


// Here the object oriented stuff kinda breaks down a bit.
// It's really messy to pass ISR callbacks on init so this has 
// to be here. Got problems with obj member funcs as function pointers.
// Could've worked with std::bind but arduino doesn't support STL.

ISR(TIMER1_COMPA_vect) {
	led.on_callback();
}

ISR(TIMER1_COMPB_vect) {
	led.off_callback();
}

ISR(PCINT2_vect)
{
	led.disco = !led.disco;
}

