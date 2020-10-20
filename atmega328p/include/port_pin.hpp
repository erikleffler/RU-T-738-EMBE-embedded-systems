#pragma once
#include "register_access.hpp"

namespace atmega328p {

template <typename Address, typename Register, const Address port,
          const Register bit>

class PortPin {
 public:
    static void setDirectionOutput() { Dir::setBit(); }

    static void setDirectionInput() { Dir::unsetBit(); }

    static void setHigh() { Port::setBit(); }

    static void setLow() { Port::unsetBit(); }

    static void toggle() { Port::toggleBit(); }

    static Register read() { Pin::getBit(); }

 private:
    static constexpr Address pdir = port - 1U;
    static constexpr Address pin = port - 2U;

    using Port = RegisterAccess<Address, Register, port, bit>;
    using Dir = RegisterAccess<Address, Register, pdir, bit>;
    using Pin = RegisterAccess<Address, Register, pin, bit>;
};

template <uint8_t address, uint8_t value>
using PortPin8 = PortPin<uint8_t, uint8_t, address, value>;

}  // namespace atmega328p

