#pragma once
#include "general.hpp"
#include "registers.hpp"
#include "utils.hpp"

namespace atmega328p {

class Timer0 {
 public:
    // Modes
    static void clear();
    static void initCtc();
    static void initPwm();

    // Compare registers
    static void setCmpA(const uint8_t compare);
    static void setCmpB(const uint8_t compare);

    static void enableCmpAInterrupt();
    static void disableCmpAInterrupt();

    static void enableCmpBInterrupt();
    static void disableCmpBInterrupt();

    static void enableOverflowInterrupt();
    static void disableOverflowInterrupt();

    // Pins for hardware PWM

    // Pwm Pin A == oc0a == D6 on sparkfun redboard
    static void disablePwmA();
    static void togglePwmAOnMatch();
    static void clearPwmAOnMatch();
    static void setPwmAOnMatch();

    // Pwm Pin B == oc0b == D5 on sparkfun redboard
    static void disablePwmB();
    static void togglePwmBOnMatch();
    static void clearPwmBOnMatch();
    static void setPwmBOnMatch();

    // Prescaler settings
    static void setPrescaler1();
    static void setPrescaler8();
    static void setPrescaler64();
    static void setPrescaler256();
    static void setPrescaler1024();

    // Getters
    static uint_fast16_t getPrescaler();

 private:
    static uint_fast16_t prescaler;

    static constexpr uint_fast8_t bottom = 0;
    static constexpr uint_fast8_t max = 255;

    // tccr0a bits
    static constexpr uint8_t wgm00 = 0;
    static constexpr uint8_t wgm01 = 1;

    static constexpr uint8_t com0b0 = 4;
    static constexpr uint8_t com0b1 = 5;
    static constexpr uint8_t com0a0 = 6;
    static constexpr uint8_t com0a1 = 7;

    // tccr0b bits
    static constexpr uint8_t cs00 = 0;
    static constexpr uint8_t cs01 = 1;
    static constexpr uint8_t cs02 = 2;

    static constexpr uint8_t wgm02 = 3;

    static constexpr uint8_t foc0a = 6;
    static constexpr uint8_t foc0b = 7;

    // timsk0 bits
    static constexpr uint8_t toie0 = 0;
    static constexpr uint8_t ocie0a = 1;
    static constexpr uint8_t ocie0b = 2;

    // tifr0 bits
    static constexpr uint8_t tov0 = 0;
    static constexpr uint8_t ocf0a = 1;
    static constexpr uint8_t ocf0b = 2;
};

}  // namespace atmega328p
