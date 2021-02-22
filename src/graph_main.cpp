/**
 * This file is used specifically for call graph generation.
 * clang-11 -S -std=c++17 -emit-llvm ./src/graph_main.cpp -o - | opt -analyze -dot-callgraph
 * 
 * 
 * 
 **/

#include <cstdint>
#include "arm7tdmi/arm7tdmi_debug.h"

int main() {
    ARM7TDMI_DEBUG<1024> *cpusim = new ARM7TDMI_DEBUG<1024>();
    
    cpusim->SetMemory32(0x0,{
        0x0100A0E3,//mov r0, #1
        0x010080E2,//add r0, #1
        0x010080E2,//add r0, #1
    });

    cpusim->cpu.EXCEP_RST();
    cpusim->cpu.Step();
    cpusim->cpu.Step();
    cpusim->cpu.Step();

    return 0;
} 