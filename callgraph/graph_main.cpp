/**
 * This file is used specifically for call graph generation.
 * 
 **/

#include <cstdint>
#include "../src/arm7tdmi/arm7tdmi.h"

class NullBus : public BusInterface {
public:
    std::uint8_t  R8   (std::uint32_t addr, bool isSeq){ return 0; }
    std::uint16_t R16  (std::uint32_t addr, bool isSeq){ return 0; }
    std::uint32_t R32  (std::uint32_t addr, bool isSeq){ return 0; }
    void          W8   (std::uint32_t addr, std::uint8_t  val, bool isSeq){  }
    void          W16  (std::uint32_t addr, std::uint16_t val, bool isSeq){  }
    void          W32  (std::uint32_t addr, std::uint32_t val, bool isSeq){  }
};

int main() {
    NullBus null_bus;
    ARM7TDMI cpu(&null_bus);
    static_for<std::size_t, 0, 0x1000>([&](auto i) {
        (cpu.*ARM7TDMI::ARMDecoder<((i & 0xFF0) << 16) | ((i & 0x00F) << 4)>())(ARMInstruction(0));
    });
    return 0;
} 