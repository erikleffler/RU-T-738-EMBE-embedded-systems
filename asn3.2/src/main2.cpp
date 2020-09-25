#include <Arduino.h>
#include "../../arduino_lib/include/timer_1.h"
#include "../../arduino_lib/include/digital_out.h"
#include <fifo.h>

Timer1 timer;
Fifo fifo;
DigitalOut led;

void setup() {

	Serial.begin(9600);
	Serial.setTimeout(-1);

	timer.init(1);
	led.init(5);
}

void loop() {

	while(!Serial.available()) {}
	char input = Serial.read();
	fifo.put(input);
	Serial.println("Putting character:");
	Serial.println(input);
	if(fifo.is_full()) {
		led.set_hi();
	}

}

ISR(TIMER1_COMPA_vect) {
	if(!fifo.is_empty()) {
		Serial.println("Consuming character:");
		Serial.println((char)fifo.get());
		led.set_lo();
	} else {
		Serial.println("Fifo is empty");
	}
}

ISR(TIMER1_COMPB_vect) {
}
