
#include "main.h"

constexpr std::size_t MEM_SIZE = 1024;
int main(void){
    ARM7TDMI_DEBUG<MEM_SIZE> *cpusim = new ARM7TDMI_DEBUG<MEM_SIZE>();
    
    cpusim->SetMemory32(0x0,{
        0x0100A0E3,//mov r0, #1
        0x010080E2,//add r0, #1
        0x010080E2,//add r0, #1
    });

    cpusim->cpu.EXCEP_RST();
    
    print("0x"); print(cpusim->cpu.instruction_register, 16); print(" : ");
    cpusim->cpu.Step();
    print("r0 is "); print(cpusim->cpu.registers[0]); print("\n");

    print("0x"); print(cpusim->cpu.instruction_register, 16); print(" : ");
    cpusim->cpu.Step();
    print("r0 is "); print(cpusim->cpu.registers[0]); print("\n");

    print("0x"); print(cpusim->cpu.instruction_register, 16); print(" : ");
    cpusim->cpu.Step();
    print("r0 is "); print(cpusim->cpu.registers[0]); print("\n");

    return 0;
}