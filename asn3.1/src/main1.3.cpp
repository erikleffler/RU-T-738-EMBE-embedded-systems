#include <Arduino.h>
#include "../../arduino_lib/include/timer_1.h"
#include "states.h"

Context context;

void setup() {
	Serial.begin(9600);
	Serial.setTimeout(-1);
}

void loop() {
	String event;

	noInterrupts();
	if(context.timeout){
		event = "timeout";
		context.timeout = false;
		interrupts();
	} else {
		interrupts();
		event = Serial.readStringUntil('\n');
	}

	Serial.println("Event: ");
	Serial.println(event);

	context.parseEvent(event);
	
}

ISR(TIMER1_COMPA_vect) {
	context.timeout = true;
}

ISR(TIMER1_COMPB_vect) {
	// Without this we get suuuuper wierd errors. The timer_1 class defines isr's on both compare regs and if this is not defined then weird stuff happens on CMP B interrupts.
}
