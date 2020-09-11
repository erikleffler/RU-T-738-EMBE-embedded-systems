#pragma once
#include <Arduino.h>

class Timer {
	
	public:
		
		void init(
			float frequency, 
			float duty_cycle
		);

		void set_duty_cycle(float duty_cycle);

	private:

		float frequency;
		float duty_cycle;

};

