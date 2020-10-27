#pragma once
#include <Arduino.h>

class DigitalIn {
	
	public:

		DigitalIn(uint8_t pin_n);

		DigitalIn();

		bool read();

		void init();

	private:

		uint8_t pin_mask;
};

