#include "./timer_1.h"

#define CLOCK_FREQ 16000000
#define COMPARE_REG(prescaler, timer_freq) CLOCK_FREQ / (timer_freq * prescaler)

void Timer1::set_compare_regs(float frequency) {

	uint16_t timer_max = 0xffff;

	if(COMPARE_REG(1, frequency) < timer_max) {
		OCR1A = COMPARE_REG(1, frequency);
		TCCR1B |= (1 << CS10);
		Serial.println("1");
	} else if(COMPARE_REG(8, frequency) < timer_max) {
		OCR1A = COMPARE_REG(8, frequency);
		TCCR1B |= (1 << CS11);
		Serial.println("8");
	} else if(COMPARE_REG(64, frequency) < timer_max) {
		OCR1A = COMPARE_REG(64, frequency);
		TCCR1B |= (1 << CS11) | (1 << CS10);
		Serial.println("64");
	} else if(COMPARE_REG(256, frequency) < timer_max) {
		OCR1A = COMPARE_REG(256, frequency);
		TCCR1B |= (1 << CS12);
		Serial.println("256");
	} else if(COMPARE_REG(1024, frequency) < timer_max) {
		Serial.println("1024");
		OCR1A = COMPARE_REG(1024, frequency);
		TCCR1B |= (1 << CS12) | (1 << CS10);
	}
	OCR1B = OCR1A;
}

void Timer1::init(float frequency) {

	this->frequency = frequency;

	noInterrupts();

	TCCR1A = 0; // Clear timer1 settings
	TCCR1B = 0; // :||
	TCNT1 = 0; // Clear timer1

	
	// Set both compare registers with given freq
	set_compare_regs(frequency);

	TCCR1B |= (1 << WGM12); // clear the timer on compare match A (Mode 4, CTC on OCR1A)
    TIMSK1 |= (1 << OCIE1A); // set interrupt on compare match A
    TIMSK1 |= (1 << OCIE1B); // set interrupt on compare match B

	TIMSK1 |= (1 << OCIE1A);  // enable timer compare on A interrupt
	TIMSK1 |= (1 << OCIE1B);  // enable timer compare on B interrupt


	interrupts();

}

void Timer1::set_a_frequency(float frequency) {

	OCR1A = (int)(COMPARE_REG(8, frequency));

}

void Timer1::set_b_frequency(float frequency) {

	OCR1B = (int)(COMPARE_REG(8, frequency));

}

void Timer1::set_duty_cycle(float duty_cycle) {
	OCR1B = (int)(duty_cycle * OCR1A);
}

void Timer1::disable() {
	TIMSK1 &= ~(1 << OCIE1A);  // Disable Timer2 interrupts.
	TIMSK1 &= ~(1 << OCIE1B);  // Disable Timer2 interrupts.
}

void Timer1::enable() {
	TIMSK1 |= (1 << OCIE1A);    // enable timer compare interrupt:
	TIMSK1 |= (1 << OCIE1B);    // enable timer compare interrupt:
	TIFR1 = 0;       			// clear  any pending interrupt
	TCNT1 = 0;                  // clear the timer value
}

