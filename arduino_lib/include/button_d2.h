#pragma once
#include <Arduino.h>
#include "timer_2.h"

class ButtonD2 {
	
	public:

		ButtonD2();

		void init();

		bool is_pressed();

		bool bouncing();

		void timer2_callback();

	private:

		Timer2 timer;

		bool recently_pressed;
};

