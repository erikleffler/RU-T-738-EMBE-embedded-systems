#pragma once
#include <avr/io.h>

class DigitalIn {
	
	public:

		bool read();

		void init(uint8_t pin);

	private:

		uint8_t pin_mask;
};

