#include <Arduino.h>
#include "digital_out.h"

#define CLOCK_FREQ 16000000
#define LEDPIN 13

#define COMPARE_REG(prescaler, timer_freq) timer_freq * CLOCK_FREQ / prescaler

DigitalOut outpin;

void setup() {

	noInterrupts();

	TCCR1A = 0; // Clear timer1 settings
	TCCR1B = 0; // :||
	TCNT1 = 0; // Clear timer1


	TCCR1B |= (1 << WGM12); // Set CTC mode, clear timer on compare match
	TCCR1B |= (1 << CS12); // Use prescaler value of 256

	OCR1A = COMPARE_REG(256, 1); // Set compare register with 1 HZ

	TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt

	interrupts();

	// Setup outpin
	outpin = DigitalOut(5);
	outpin.init();
}

ISR(TIMER1_COMPA_vect) {
	outpin.toggle();
}

void loop() {

}
