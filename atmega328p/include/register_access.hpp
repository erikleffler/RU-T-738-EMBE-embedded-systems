#pragma once
#include <stdint.h>

namespace atmega328p {

template <typename Address, typename Register, const Address address,
          const Register value = 0>

class RegisterAccess {
 public:
    static void setReg() {
        *reinterpret_cast<volatile Register*>(address) = value;
    }

    static void orReg() {
        *reinterpret_cast<volatile Register*>(address) |= value;
    }

    static void andReg() {
        *reinterpret_cast<volatile Register*>(address) &= value;
    }

    static Register getReg() {
        return *reinterpret_cast<volatile Register*>(address);
    }

    static void setBit() {
        *reinterpret_cast<volatile Register*>(address) |=
            Register(Register(1U) << value);
    }

    static void unsetBit() {
        *reinterpret_cast<volatile Register*>(address) &=
            ~Register(Register(1U) << value);
    }

    static void toggleBit() {
        *reinterpret_cast<volatile Register*>(address) ^=
            Register(Register(1U) << value);
    }

    static Register getBit() {
        return *reinterpret_cast<volatile Register*>(address) &
               Register(Register(1U) << value);
    }

    static void setReg(const Register run_time_value) {
        *reinterpret_cast<volatile Register*>(address) = run_time_value;
    }

    static void orReg(const Register run_time_value) {
        *reinterpret_cast<volatile Register*>(address) |= run_time_value;
    }

    static void andReg(const Register run_time_value) {
        *reinterpret_cast<volatile Register*>(address) &= run_time_value;
    }

    static Register getReg(const Register run_time_value) {
        return *reinterpret_cast<volatile Register*>(address);
    }

    static void setBit(const Register run_time_value) {
        *reinterpret_cast<volatile Register*>(address) |=
            Register(Register(1U) << run_time_value);
    }

    static void unsetBit(const Register run_time_value) {
        *reinterpret_cast<volatile Register*>(address) &=
            ~Register(Register(1U) << run_time_value);
    }

    static void toggleBit(const Register run_time_value) {
        *reinterpret_cast<volatile Register*>(address) ^=
            Register(Register(1U) << run_time_value);
    }

    static Register getBit(const Register run_time_value) {
        return *reinterpret_cast<volatile Register*>(address) &
               Register(Register(1U) << run_time_value);
    }
};

template <uint8_t address, uint8_t value = 0>
using RegisterAccess8 = RegisterAccess<uint8_t, uint8_t, address, value>;

}  // namespace atmega328p

