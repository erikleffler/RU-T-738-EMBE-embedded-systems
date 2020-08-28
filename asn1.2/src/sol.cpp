#include <Arduino.h>
#include "digital_out.h"
#include "digital_in.h"

DigitalOut outpin;
DigitalIn inpin;

void setup() {
	outpin = DigitalOut(5);
	inpin = DigitalIn(4);
	outpin.init();
	inpin.init();

}

void loop() {

	if(inpin.read()) {
		outpin.set_lo();
	} else {
		outpin.toggle();
	}
	delay(100);
}


