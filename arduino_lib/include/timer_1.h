#pragma once
#include <Arduino.h>

class Timer1 {
	
	public:
		
		void init(float frequency);

		void set_a_frequency(float frequency);

		void set_b_frequency(float frequency);

		void set_duty_cycle(float duty_cycle);

		void enable();

		void disable();

	private:

		float frequency;

		void set_compare_regs(float frequency);

};

