#pragma once
#include <Arduino.h>

class DigitalOut {
	
	public:

		DigitalOut(uint8_t pin_n);

		DigitalOut();

		void init();

		void set_hi();

		void set_lo();

		void toggle();

	private:

		uint8_t pin_mask;
};

