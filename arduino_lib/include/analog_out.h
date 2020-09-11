#pragma once
#include <Arduino.h>
#include "timer.h"
#include "digital_out.h"

class AnalogOut {
	
	public:

		bool disco;

		void init(uint8_t pin);

		void set_val(uint8_t value);

		void set_hi();

		void set_lo();

		void on_callback();

		void off_callback();

	private:

		uint8_t pin;
		DigitalOut digital_out;
		Timer timer;
};

