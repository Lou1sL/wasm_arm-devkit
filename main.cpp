
#include "main.h"

constexpr std::size_t MEM_SIZE = 1024;
int main(void){
    ARM7TDMI_DEBUG<MEM_SIZE> *cpu = new ARM7TDMI_DEBUG<MEM_SIZE>();
    return 0;
}

//for(var i=0; i<0x20000; i++) if(SIM_memget(i) == 0x69) console.log(i.toString(16))