#pragma once
#include <stdint.h>

#include "port_pin.hpp"

namespace atmega328p {

namespace regs {

// Bit field struct for bit specific settings

typedef struct Bits8 {
    uint8_t b0 : 1;
    uint8_t b1 : 1;
    uint8_t b2 : 1;
    uint8_t b3 : 1;
    uint8_t b4 : 1;
    uint8_t b5 : 1;
    uint8_t b6 : 1;
    uint8_t b7 : 1;
} Bits8;

typedef union Register8 {
    uint8_t value;
    Bits8 bits;
} Register8;

/*
        ##### PORT PINS #####
*/

// Direction registers
constexpr uint8_t ddrb = UINT8_C(0x24);
constexpr uint8_t ddrc = UINT8_C(0x27);
constexpr uint8_t ddrd = UINT8_C(0x2a);

// Port registsers
constexpr uint8_t portb = UINT8_C(0x25);
constexpr uint8_t portc = UINT8_C(0x28);
constexpr uint8_t portd = UINT8_C(0x2b);

// Pin registsers
constexpr uint8_t pinb = UINT8_C(0x23);
constexpr uint8_t pinc = UINT8_C(0x26);
constexpr uint8_t pind = UINT8_C(0x29);

// Port pins
const PortPin8<portb, 0> portb0;
const PortPin8<portb, 1> portb1;
const PortPin8<portb, 2> portb2;
const PortPin8<portb, 3> portb3;
const PortPin8<portb, 4> portb4;
const PortPin8<portb, 5> portb5;
const PortPin8<portb, 6> portb6;
const PortPin8<portb, 7> portb7;

const PortPin8<portc, 0> portc0;
const PortPin8<portc, 1> portc1;
const PortPin8<portc, 2> portc2;
const PortPin8<portc, 3> portc3;
const PortPin8<portc, 4> portc4;
const PortPin8<portc, 5> portc5;
const PortPin8<portc, 6> portc6;
const PortPin8<portc, 7> portc7;

const PortPin8<portd, 0> portd0;
const PortPin8<portd, 1> portd1;
const PortPin8<portd, 2> portd2;
const PortPin8<portd, 3> portd3;
const PortPin8<portd, 4> portd4;
const PortPin8<portd, 5> portd5;
const PortPin8<portd, 6> portd6;
const PortPin8<portd, 7> portd7;

/*
        ##### TIMER RELATED REGISTERS #####
*/

// Timer 0
constexpr uint8_t tccr0a = UINT8_C(0x44);
constexpr uint8_t tccr0b = UINT8_C(0x44);
constexpr uint8_t tcnt0 = UINT8_C(0x46);
constexpr uint8_t ocr0a = UINT8_C(0x47);
constexpr uint8_t ocr0b = UINT8_C(0x48);
constexpr uint8_t timsk0 = UINT8_C(0x6e);
constexpr uint8_t tifr0 = UINT8_C(0x35);

// Timer 1
constexpr uint8_t tccr1a = UINT8_C(0x80);
constexpr uint8_t tccr1b = UINT8_C(0x81);
constexpr uint8_t tccr1c = UINT8_C(0x82);
constexpr uint8_t tcnt1l = UINT8_C(0x84);
constexpr uint8_t tcnt1h = UINT8_C(0x85);
constexpr uint8_t ocr1al = UINT8_C(0x88);
constexpr uint8_t ocr1ah = UINT8_C(0x89);
constexpr uint8_t ocr1bl = UINT8_C(0x8a);
constexpr uint8_t ocr1bh = UINT8_C(0x8b);
constexpr uint8_t icr1l = UINT8_C(0x86);
constexpr uint8_t icr1h = UINT8_C(0x87);
constexpr uint8_t timsk1 = UINT8_C(0x6f);
constexpr uint8_t tifr1 = UINT8_C(0x36);

// Timer 2
constexpr uint8_t tccr2a = UINT8_C(0xb0);
constexpr uint8_t tccr2b = UINT8_C(0xb1);
constexpr uint8_t tcnt2 = UINT8_C(0xb2);
constexpr uint8_t ocr2a = UINT8_C(0xb3);
constexpr uint8_t ocr2b = UINT8_C(0xb4);
constexpr uint8_t timsk2 = UINT8_C(0x70);
constexpr uint8_t tifr2 = UINT8_C(0x37);

}  // namespace regs
}  // namespace atmega328p
