#include "timer0.hpp"



namespace atmega328p {

uint_fast16_t Timer0::prescaler;

void Timer0::clear() {
    // Clear pending interrupts
    RegisterAccess8<regs::tifr0, 0>::setReg();

    // Clear timer settings

    RegisterAccess8<regs::tccr0a, 0>::setReg();
    RegisterAccess8<regs::tccr0b, 0>::setReg();

    // Clear timer counter
    RegisterAccess8<regs::tcnt0, 0>::setReg();
}

void Timer0::initCtc() {
    Timer0::clear();

    RegisterAccess8<regs::tccr0a, wgm01>::setBit();
}

void Timer0::initPwm() {
    Timer0::clear();
    RegisterAccess8<regs::tccr0a, bits<uint8_t, wgm00, wgm01>()>::setReg();
}

void Timer0::setCmpA(const uint8_t compare) {
    RegisterAccess8<regs::ocr0a>::setReg(compare);
}

void Timer0::setCmpB(const uint8_t compare) {
    RegisterAccess8<regs::ocr0b>::setReg(compare);
}

void Timer0::enableCmpAInterrupt() {
    RegisterAccess8<regs::timsk0, ocie0a>::setBit();
}

void Timer0::disableCmpAInterrupt() {
    RegisterAccess8<regs::timsk0, ocie0a>::unsetBit();
}

void Timer0::enableCmpBInterrupt() {
    RegisterAccess8<regs::timsk0, ocie0b>::setBit();
}

void Timer0::disableCmpBInterrupt() {
    RegisterAccess8<regs::timsk0, ocie0b>::unsetBit();
}

void Timer0::enableOverflowInterrupt() {
    RegisterAccess8<regs::timsk0, toie0>::setBit();
}

void Timer0::disableOverflowInterrupt() {
    RegisterAccess8<regs::timsk0, toie0>::unsetBit();
}

// Bellow are the different configurations for the OC0x pins
// Here is the truth table:
//
// COM0x1	| COM0x0	| OC0x
// 0		| 0			| Disabled, normal pin operation
// 1		| 0			| Toggle on match (ONLY VALID IN CTC
// MODE) 0		| 1			| Clear on match. If PWM, set on
// bottom 1		| 1			| Set on match. If PWM, clear on
// bottom

void Timer0::disablePwmA() {
    RegisterAccess8<regs::tccr0a,
                    uint8_t(~bits<uint8_t, com0a0, com0a1>())>::andReg();
}

void Timer0::togglePwmAOnMatch() {
    RegisterAccess8<regs::tccr0a, com0a0>::setBit();

    RegisterAccess8<regs::tccr0a, com0a1>::unsetBit();
}

void Timer0::clearPwmAOnMatch() {
    RegisterAccess8<regs::tccr0a, com0a0>::unsetBit();

    RegisterAccess8<regs::tccr0a, com0a1>::setBit();
}

void Timer0::setPwmAOnMatch() {
    RegisterAccess8<regs::tccr0a, bits<uint8_t, com0a0, com0a1>()>::orReg();
}

void Timer0::disablePwmB() {
    RegisterAccess8<regs::tccr0a,
                    uint8_t(~bits<uint8_t, com0b0, com0b1>())>::andReg();
}

void Timer0::togglePwmBOnMatch() {
    RegisterAccess8<regs::tccr0a, com0b0>::setBit();

    RegisterAccess8<regs::tccr0a, com0b1>::unsetBit();
}

void Timer0::clearPwmBOnMatch() {
    RegisterAccess8<regs::tccr0a, com0b0>::unsetBit();

    RegisterAccess8<regs::tccr0a, com0b1>::setBit();
}

void Timer0::setPwmBOnMatch() {
    RegisterAccess8<regs::tccr0a, bits<uint8_t, com0b0, com0a1>()>::orReg();
}

void Timer0::setPrescaler1() {
    Timer0::prescaler = 1;

    RegisterAccess8<regs::tccr0b, cs00>::setBit();

    RegisterAccess8<regs::tccr0b,
                    uint8_t(~bits<uint8_t, cs01, cs02>())>::andReg();
}

void Timer0::setPrescaler8() {
    Timer0::prescaler = 8;

    RegisterAccess8<regs::tccr0b, cs01>::setBit();

    RegisterAccess8<regs::tccr0b,
                    uint8_t(~bits<uint8_t, cs00, cs02>())>::andReg();
}

void Timer0::setPrescaler64() {
    Timer0::prescaler = 64;

    RegisterAccess8<regs::tccr0b, bits<uint8_t, cs00, cs01>()>::orReg();

    RegisterAccess8<regs::tccr0b, cs01>::unsetBit();
}

void Timer0::setPrescaler256() {
    Timer0::prescaler = 256;

    RegisterAccess8<regs::tccr0b,
                    uint8_t(~bits<uint8_t, cs00, cs01>())>::andReg();

    RegisterAccess8<regs::tccr0b, cs02>::setBit();
}

void Timer0::setPrescaler1024() {
    Timer0::prescaler = 1024;

    RegisterAccess8<regs::tccr0b, cs01>::unsetBit();

    RegisterAccess8<regs::tccr0b, bits<uint8_t, cs00, cs02>()>::orReg();
}

uint_fast16_t Timer0::getPrescaler() { return Timer0::prescaler; }
}  // namespace atmega328p
