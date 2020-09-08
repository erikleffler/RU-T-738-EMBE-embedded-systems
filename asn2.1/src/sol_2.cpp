#include <Arduino.h>
#include "digital_out.h"

#define CLOCK_FREQ 16000000
#define LEDPIN 13

#define COMPARE_REG(prescaler, timer_freq) timer_freq * CLOCK_FREQ / prescaler

DigitalOut outpin;

void setup() {

	float on = 0.8;
	float timer_freq = 0.1;

	noInterrupts();

	// OBS - Don't use CTC, want to keep counting between int A and B.
	
	TCCR1A = 0; // Clear timer1 settings
	TCCR1B = 0; // :||
	TCNT1 = 0; // Clear timer1

	TCCR1B |= (1 << CS12); // Use prescaler value of 256 

	OCR1A = (int)((1 - on) * COMPARE_REG(256, timer_freq)); // Be turned off for (1-on) * timer_freq
	OCR1B = (int)(COMPARE_REG(256, timer_freq)); // Be turned on for remaining time

	TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt on A
	TIMSK1 |= (1 << OCIE1B);  // enable timer compare interrupt on B
	
	interrupts();

	// Setup outpin
	outpin = DigitalOut(5);
	outpin.init();
}

ISR(TIMER1_COMPA_vect) {
	outpin.set_hi();
}

ISR(TIMER1_COMPB_vect) {
	outpin.set_lo();
	TCNT1 = 0; // Clear timer1
}

void loop() {

}
