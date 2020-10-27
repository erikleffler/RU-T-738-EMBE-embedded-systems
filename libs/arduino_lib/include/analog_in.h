#pragma once
#include <Arduino.h>

class AnalogIn {
	
	public:

		uint8_t read();

		void init(uint8_t pin);

	private:

		uint8_t pin;
};
