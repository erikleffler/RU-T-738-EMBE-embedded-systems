#include "registers.hpp"
#include "timer0.hpp"

int xp;

int main() {
    atmega328p::Timer0::initPwm();
    atmega328p::Timer0::setCmpA(100);
    atmega328p::Timer0::setPrescaler1();
    atmega328p::Timer0::setPwmAOnMatch();

    xp = 2;
    int y = xp + 2;
    while (true) {
    }
}
void lol() {
    int x = 2;
    int y = 3
}
