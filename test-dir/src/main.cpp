#include "registers.hpp"
#include "interrupts.hpp"
#include "timer0.hpp"

uint8_t cmpa = 0;

int main() {
    atmega328p::regs::portd6.setDirectionOutput();
    atmega328p::Timer0::initPwm();
    atmega328p::Timer0::setCmpA(cmpa);
    atmega328p::Timer0::setCmpB(255);
    atmega328p::Timer0::clearPwmAOnMatch();
    atmega328p::Timer0::enableCmpBInterrupt();
    atmega328p::Timer0::setPrescaler1024();

	sei();

	atmega328p::regs::portb5.setDirectionOutput();
	atmega328p::regs::portb5.setHigh();
	while(1) {}
}
