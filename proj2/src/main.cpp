#include <Arduino.h>
#include "../../arduino_lib/include/timer.h"
#include "../../arduino_lib/include/analog_out.h"
#include "../../arduino_lib/include/analog_in.h"
/*
#include "../../arudino_lib/button.h"

Button button;
*/
Timer timer;
AnalogOut led;
AnalogIn photocell;

void setup() {

	Serial.begin(9600);
	// Timer setup
	timer.init(2);

   	// LED setup
	led.init(3);

	// Photocell setup
	photocell.init(A0);
/*


	// Button setup
	button = Button(12);
	button.init()
	button.set_intterupt_func(
		[&timer, &led] (void) {
			timer.set_interrupt_func(led.toggle());
		}
	);*/
}

/*
ISR(TIMER1_COMPA_vect) {
	led.toggle();
}*/

void loop() {
	led.set_val(255 - photocell.read());
	Serial.println(photocell.read());
}
