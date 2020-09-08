#pragma once
#include <Arduino.h>

class AnalogOut {
	
	public:

		void init(uint8_t pin);

		void set_hi();

		void set_val(uint8_t value);

		void set_lo();

		void toggle();

	private:

		uint8_t pin;
		bool is_low;
};

