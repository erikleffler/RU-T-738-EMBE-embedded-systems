#include <Arduino.h>
#include "../../arduino_lib/include/timer_1.h"

enum state {Green, Yellow, Red}state;
bool timeout = false;

Timer1 timer5s;

void setup() {
	Serial.begin(9600);
	Serial.setTimeout(-1);
	timer5s.init(0.2); // 0.2hz => wait 5s
	timer5s.disable();
	state = Red;
	Serial.println("Start state -> Red");
}

void loop() {
	String event;

	if(timeout){
		event = "timeout";
		timeout = false;
	} else {
		event = Serial.readStringUntil('\n');
	}

	Serial.println("Event: ");
	Serial.println(event);

	
	switch(state) {
	
		case Green:
			if(event == "stop") {
				Serial.println("Green - exit / turn off green light");
				state = Yellow;
				Serial.println("Green -> Yellow");
				Serial.println("Yellow - entry / turn on yellow light");
				Serial.println("Yellow - entry / turn on timer");
				timer5s.enable();
			}

		case Yellow:
			if(event == "timeout") {
				Serial.println("Yellow - exit / turn off yellow light");
				state = Red;
				Serial.println("Yellow -> Red");
				Serial.println("Red - entry / turn on red light");
			}
	
		case Red:
			if(event == "go") {
				Serial.println("Red - exit / turn off red light");
				state = Green;
				Serial.println("Red -> Green");
				Serial.println("Green - entry / turn on green light");
			}
	}

}
ISR(TIMER1_COMPA_vect) {
	timeout=true;
	timer5s.disable();
}
