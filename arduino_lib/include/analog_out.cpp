#include "analog_out.h"

void AnalogOut::init(uint8_t pin) {
	this->pin = pin;
	this->is_low = true;
	pinMode(this->pin, OUTPUT);
}

void AnalogOut::set_hi() {
	this->is_low = false;
	analogWrite(this->pin, 255);
}

void AnalogOut::set_val(uint8_t value) {
	this->is_low = (bool)value;
	analogWrite(this->pin, value);
}

void AnalogOut::set_lo() {
	this->is_low = true;
	analogWrite(this->pin, 0);
}

void AnalogOut::toggle() {

	if(this->is_low) {
		this->set_hi();
	} else {
		this->set_lo();
	}
}
