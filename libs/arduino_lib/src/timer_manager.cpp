#include "./timer_manager.h"

TimerManager TimerManager::singleton_instance;

ISRCbNode::ISRCbNode(
		void (*cb)(),
		float freq,
		bool repeating,
		ISRCbNode* next,
		ISRCbNode* prev
	) : 
	cb(cb),
	freq(freq),
	repeating(repeating),
	next(next),
	prev(prev)
{
	if(next)
		next->prev = this;

	if(prev)
		prev->next = this;
}

void ISRCbNode::Unlink() { 

	if(this->next)
		this->next->prev = this->prev;

	if(this->prev)
		this->prev->next = this->next;
}

Timer::Timer(uint16_t max_compare) : 
	max_compare(max_compare),
	prescaler(1),
	cmp_a_callbacks(nullptr),
	cmp_b_callbacks(nullptr)
{
	
}

void Timer0::init() {
	TCCR0A = 0; // Clear timer0 settings
	TCCR0B = 0; // :||
	TCNT0 = 0; // Clear timer0

	TCCR0B |= (1 << WGM02); // clear the timer on compare match A (Mode 4, CTC on OCR0A)
    TIMSK0 |= (1 << OCIE0A); // set interrupt on compare match A
    TIMSK0 |= (1 << OCIE0B); // set interrupt on compare match B
}

void Timer1::init() {
	TCCR1A = 0; // Clear timer0 settings
	TCCR1B = 0; // :||
	TCNT1 = 0; // Clear timer0

	TCCR1B |= (1 << WGM12); // clear the timer on compare match A (Mode 4, CTC on OCR0A)
    TIMSK1 |= (1 << OCIE1A); // set interrupt on compare match A
    TIMSK1 |= (1 << OCIE1B); // set interrupt on compare match B
}

void Timer2::init() {
	TCCR2A = 0; // Clear timer0 settings
	TCCR2B = 0; // :||
	TCNT2 = 0; // Clear timer0

	TCCR2B |= (1 << WGM22); // clear the timer on compare match A (Mode 4, CTC on OCR0A)
    TIMSK2 |= (1 << OCIE2A); // set interrupt on compare match A
    TIMSK2 |= (1 << OCIE2B); // set interrupt on compare match B
}

TimerManager::TimerManager() :
	timer0(0xff),
	timer1(0xfff),
	timer2(0xff)
{
	timer0.init();
	timer1.init();
	timer2.init();

}

TimerManager& TimerManager::GetInstance() {
	return singleton_instance;
}
void TimerManager::Timer0CompareA(){
	
}

void TimerManager::Timer0CompareB(){

}

void TimerManager::Timer1CompareA(){

}

void TimerManager::Timer1CompareB(){

}

void TimerManager::Timer2CompareA(){

}

void TimerManager::Timer2CompareB(){

}


ISR(TIMER0_COMPA_vect) {
	TimerManager::GetInstance().Timer0CompareA();
}

ISR(TIMER0_COMPB_vect) {
	TimerManager::GetInstance().Timer0CompareB();
}

ISR(TIMER1_COMPA_vect) {
	TimerManager::GetInstance().Timer1CompareA();
}

ISR(TIMER1_COMPB_vect) {
	TimerManager::GetInstance().Timer1CompareB();
}

ISR(TIMER2_COMPA_vect) {
	TimerManager::GetInstance().Timer2CompareA();
}

ISR(TIMER2_COMPB_vect) {
	TimerManager::GetInstance().Timer2CompareB();
}

