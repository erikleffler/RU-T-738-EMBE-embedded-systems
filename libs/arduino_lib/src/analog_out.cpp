#include "analog_out.h"

void AnalogOut::init(uint8_t pin) {
	this->pin = pin;
	this->disco = false;

	this->digital_out = DigitalOut();
	this->digital_out.init(this->pin);

	this->timer = Timer1(); // Start off

	this->timer.init(300);
}


void AnalogOut::set_val(uint8_t value) {

	if(!this->disco) {
		this->timer.set_duty_cycle(value / 255.0);
	} else {
		delay(500);
		this->digital_out.toggle();
	}
}

void AnalogOut::set_hi() {
	this->timer.set_duty_cycle(1); // turn on
}

void AnalogOut::set_lo() {
	this->timer.set_duty_cycle(0); // turn off
}

void AnalogOut::on_callback() {
	if(!this->disco) {
		this->digital_out.set_hi();
	}
}

void AnalogOut::off_callback() {
	if(!this->disco) {
		this->digital_out.set_lo();
	}
}
