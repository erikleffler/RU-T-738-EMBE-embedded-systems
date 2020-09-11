#include "./timer.h"

#define CLOCK_FREQ 16000000
#define COMPARE_REG(prescaler, timer_freq) timer_freq * CLOCK_FREQ / prescaler


void Timer::init(
		float frequency, 
		float duty_cycle 
) {

	this->frequency = frequency;
	this->duty_cycle = duty_cycle;

	noInterrupts();

	TCCR1A = 0; // Clear timer1 settings
	TCCR1B = 0; // :||
	TCNT1 = 0; // Clear timer1

	TCCR1B |= (1 << CS11); // Use prescaler value of 256
	
	// Set compare register with given freq
	OCR1A = (int)(COMPARE_REG(8, this->frequency));
	OCR1B = (int)(OCR1A * this->duty_cycle);

	TCCR1B |= (1 << WGM12); // clear the timer on compare match A (Mode 4, CTC on OCR1A)
    TIMSK1 |= (1 << OCIE1A); // set interrupt on compare match A
    TIMSK1 |= (1 << OCIE1B); // set interrupt on compare match B

	TIMSK1 |= (1 << OCIE1A);  // enable timer compare on A interrupt
	TIMSK1 |= (1 << OCIE1B);  // enable timer compare on B interrupt

	interrupts();

}

void Timer::set_duty_cycle(float duty_cycle) {
	
	noInterrupts();

	this->duty_cycle = duty_cycle;
	
	// Set compare register with given freq
	OCR1A = (int)(COMPARE_REG(256, this->frequency));
	OCR1B = (int)(OCR1A * this->duty_cycle);

	interrupts();
}

