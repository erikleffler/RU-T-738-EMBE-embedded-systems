#include "./timer_2.h"

#define CLOCK_FREQ 16000000
#define COMPARE_REG(prescaler, timer_freq) CLOCK_FREQ / (timer_freq * prescaler)

void Timer2::set_compare_regs(float frequency) {

	uint8_t timer_max = 0xff;

	if(COMPARE_REG(1, frequency) < timer_max) {
		OCR2A = COMPARE_REG(1, frequency);
		TCCR2B |= (1 << CS20);
		Serial.println("1");
	} else if(COMPARE_REG(8, frequency) < timer_max) {
		OCR2A = COMPARE_REG(8, frequency);
		TCCR2B |= (1 << CS21);
		Serial.println("8");
	} else if(COMPARE_REG(64, frequency) < timer_max) {
		OCR2A = COMPARE_REG(64, frequency);
		TCCR2B |= (1 << CS21) | (1 << CS20);
		Serial.println("64");
	} else if(COMPARE_REG(256, frequency) < timer_max) {
		OCR2A = COMPARE_REG(256, frequency);
		TCCR2B |= (1 << CS22);
		Serial.println("256");
	} else if(COMPARE_REG(1024, frequency) < timer_max) {
		Serial.println("1024");
		OCR2A = COMPARE_REG(1024, frequency);
		TCCR2B |= (1 << CS22) | (1 << CS20);
	} else {
		Serial.println("fail");
	}

	OCR2B = OCR2A;
}

void Timer2::init(float frequency) {

	this->frequency = frequency;

	noInterrupts();

	TCCR2A = 0; // Clear timer2 settings
	TCCR2B = 0; // :||
	TCNT2 = 0; // Clear timer2

	
	// Set both compare registers with given freq

	TCCR2B |= (1 << WGM22); // clear the timer on compare match A (Mode 4, CTC on OCR2A)
    TIMSK2 |= (1 << OCIE2A); // set interrupt on compare match A
    TIMSK2 |= (1 << OCIE2B); // set interrupt on compare match B

	this->set_compare_regs(frequency);

	interrupts();

}

void Timer2::set_a_frequency(float frequency) {

	OCR2A = (int)(COMPARE_REG(8, frequency));

}

void Timer2::set_b_frequency(float frequency) {

	OCR2B = (int)(COMPARE_REG(8, frequency));

}

void Timer2::set_duty_cycle(float duty_cycle) {
	OCR2B = (int)(duty_cycle * OCR2A);
}

void Timer2::disable() {
	TIMSK2 &= ~(1 << OCIE2A);  // Disable Timer2 interrupts.
	TIMSK2 &= ~(1 << OCIE2B);  // Disable Timer2 interrupts.
}

void Timer2::enable() {
	TIMSK2 |= (1 << OCIE2A);    // enable timer compare interrupt:
	TIMSK2 |= (1 << OCIE2B);    // enable timer compare interrupt:
	TIFR2 = 0;       			// clear  any pending interrupt
	TCNT2 = 0;                  // clear the timer value
}

