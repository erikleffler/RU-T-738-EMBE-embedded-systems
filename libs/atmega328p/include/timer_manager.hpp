#pragma once

#include "general.hpp"
#include "interrupts.hpp"
#include "timer0.hpp"

namespace atmega328p {

class TimerManager {
 public:
    using FunctionPtr = void (*)();

    static bool attachFunctionToTimer(FunctionPtr f, uint32_t nanoseconds);

 private:
    template <typename Func, typename... Args>

    class callback {
     public:
        const FunctionPtr cb;
        const uint32_t nanoseconds;
    };

    friend void TIMER0_COMPA_vect(void);
    friend void TIMER0_COMPB_vect(void);
};
}  // namespace atmega328p
