#include <Arduino.h>
#include "../../arduino_lib/include/button_d2.h"
#include "../../arduino_lib/include/analog_out.h"
#include "../../arduino_lib/include/analog_in.h"
#include "../../arduino_lib/include/exp_filter.h"

ButtonD2 button;
AnalogOut led;
AnalogIn input;
ExpFilter input_filter;

void setup() {

	Serial.begin(9600);

   	// LED setup
	led.init(5);

	// Analog input setup
	input.init(A0);

	// Button setup
	button.init();

	input_filter = ExpFilter(0.04);

}

void loop() {
	float filtered_analog_input = input_filter.filter(input.read());
	led.set_val(255 - filtered_analog_input);
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


ISR(TIMER2_COMPA_vect) {
	button.timer2_callback();
}


ISR(PCINT2_vect)
{
	if(!button.bouncing()) {
		led.disco = !led.disco;
	}
}

