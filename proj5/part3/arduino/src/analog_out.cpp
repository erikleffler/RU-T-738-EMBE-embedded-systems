#include <analog_out.h>

Analog_out::Analog_out(int pin) {
    this->pin = pin; 
    pinMask = (1 << pin);
}

// Set chosen pin to output
void Analog_out::init() {
    DDRD |= pinMask;   
	//pinMode(this->pin, OUTPUT); 
	this->is_low = true;        
}

void Analog_out::set_val(uint8_t value) {
	this->is_low = !(bool)value;    // 0 = false
	analogWrite(this->pin, value);
}

void Analog_out::set_hi() {
	this->is_low = false;
	analogWrite(this->pin, 255);
}

void Analog_out::set_lo() {
	this->is_low = true;
	analogWrite(this->pin, 0);
}

void Analog_out::toggle() {
	delay(TIME);

	if(this->is_low) {
		this->set_hi();
	} else {
		this->set_lo();
	}
}