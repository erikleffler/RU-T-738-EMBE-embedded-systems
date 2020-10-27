#pragma once
#include <Arduino.h>

class DigitalOut {
	
	public:

		void init(uint8_t pin);

		void set_hi();

		void set_lo();

		void toggle();

	private:

		uint8_t pin_mask;
};

