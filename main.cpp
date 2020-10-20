
#include "main.h"

constexpr std::size_t MEM_SIZE = 1024;
int main(void){
    ARM7TDMI_DEBUG<MEM_SIZE> *cpusim = new ARM7TDMI_DEBUG<MEM_SIZE>();
    
    cpusim->SetMemory32(0x0,{
        0x0100A0E3,//mov r0, #1
        0x010080E2,//add r0, #1
        0x010080E2,//add r0, #1
        0x010080E2,//add r0, #1
    });
    print("0x"); print(cpusim->main_bus.R32(0x0, false), 16); print("\n");
    print("0x"); print(cpusim->main_bus.R32(0x4, false), 16); print("\n");
    print("0x"); print(cpusim->main_bus.R32(0x8, false), 16); print("\n");
    print("0x"); print(cpusim->main_bus.R32(0xC, false), 16); print("\n");

    cpusim->cpu.EXCEP_RST();
    cpusim->cpu.Step();
    print(cpusim->cpu.registers[0]); print("\n");
    cpusim->cpu.Step();
    print(cpusim->cpu.registers[0]); print("\n");
    cpusim->cpu.Step();
    print(cpusim->cpu.registers[0]); print("\n");
    cpusim->cpu.Step();
    print(cpusim->cpu.registers[0]); print("\n");
    return 0;
}

//for(var i=0; i<0x20000; i++) if(SIM_memget(i) == 0x69) console.log(i.toString(16))