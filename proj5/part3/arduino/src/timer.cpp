#include <timer.h>
#include <Arduino.h>

Timer::Timer()
{
}

void Timer::stop()
{
    // disable all interrupts
    //noInterrupts(); 
    
    // this code sets up timer1 for a 1 s  @ 16Mhz system clock (mode 4)
    TCCR1A = 0; // set entire TCCR1A register to 0
    TCCR1B = 0; // same for TCCR1B
    TCNT1 = 0;  //initialize counter value to 0
}

void Timer::start(int frequ)
{
    frequency = 16000000 / 1024 - 1;
    frequency = int(frequency / frequ);
    OCR1A = frequency;         // assign target count to compare register A (must be less than 65536)
    TCCR1B |= (1 << WGM12);              // clear the timer on compare match A (Mode 4, CTC on OCR1A)
    TIMSK1 |= (1 << OCIE1A);             // set interrupt on compare match A
    TCCR1B |= (1 << CS12) | (1 << CS10); // set prescaler to 1024 and start the timer

    sei(); // enable interrupts
}


