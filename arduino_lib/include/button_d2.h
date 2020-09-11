#pragma once
#include <Arduino.h>

class ButtonD2 {
	
	public:

		void init();

		bool is_pressed();

		bool debounced();
};

