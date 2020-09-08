#include "timer.h"

#define CLOCK_FREQ 16000000
#define COMPARE_REG(prescaler, timer_freq) timer_freq * CLOCK_FREQ / prescaler

void Timer::init(float frequency) {

	this->frequency = frequency;

	noInterrupts();

	TCCR1A = 0; // Clear timer1 settings
	TCCR1B = 0; // :||
	TCNT1 = 0; // Clear timer1


	TCCR1B |= (1 << WGM12); // Set CTC mode, clear timer on compare match
	TCCR1B |= (1 << CS12); // Use prescaler value of 256
	
	// Set compare register with given freq
	OCR1A = (int)(COMPARE_REG(256, this->frequency));

	TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt

	interrupts();

}
