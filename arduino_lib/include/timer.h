#pragma once
#include <Arduino.h>

class Timer {
	
	public:

		void init(float frequency);

	private:

		float frequency;
};

