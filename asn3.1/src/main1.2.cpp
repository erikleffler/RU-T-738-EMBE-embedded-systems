#include <Arduino.h>
#include "../../arduino_lib/include/timer_1.h"

enum state {Green, Yellow, Red}state;
bool timeout = false;
Timer1 timer5s;

void setup() {
	Serial.begin(9600);
	Serial.setTimeout(-1);
	timer5s.init(0.25); // 0.25hz => wait 4s
	timer5s.disable();
	state = Red;
	Serial.println("Start state -> Red");
}

void loop() {
	String event;

	noInterrupts();
	if(timeout){
		event = "timeout";
		timeout = false;
		interrupts();
	} else {
		interrupts();
		event = Serial.readStringUntil('\n');
	}

	Serial.println("Event: ");
	Serial.println(event);

	
	switch(state) {
	
		case Green:
			if(event.indexOf("stop") != -1) {
				Serial.println("Green - exit / turn off green light");
				state = Yellow;
				Serial.println("Green -> Yellow");
				Serial.println("Yellow - entry / turn on yellow light");
				Serial.println("Yellow - entry / turn on timer");
				timer5s.enable();
			}
			break;

		case Yellow:
			if(event.indexOf("timeout") != -1) {
				Serial.println("Yellow - exit / turn off yellow light");
				state = Red;
				Serial.println("Yellow -> Red");
				Serial.println("Red - entry / turn on red light");
			}
			break;
	
		case Red:
			if(event.indexOf("go") != -1) {
				Serial.println("Red - exit / turn off red light");
				state = Green;
				Serial.println("Red -> Green");
				Serial.println("Green - entry / turn on green light");
			}
			break;
	}

}

ISR(TIMER1_COMPA_vect) {
	timeout=true;
	timer5s.disable();
}

ISR(TIMER1_COMPB_vect) {
	// Without this we get suuuuper wierd errors. The timer_1 class defines isr's on both compare regs and if this is not defined then weird stuff happens on CMP B interrupts.
}
