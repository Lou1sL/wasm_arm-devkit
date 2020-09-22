#include "main.h"


const char moo[] = 
    "^__^\n"
    "(oo)\\_______\n"
    "(__)\\       )\\/\\\n"
    "    ||----w |\n"
    "    ||     ||\n\n"
    "WELCOME TO WASM_ARM!!\n";

int main(void){
    asm("MSR cpsr_c,#(0b11111)");// Enable IRQ
    SET_IRQ_EXCEP_HANDLER([](){ print("AN IRQ BEFORE & DURING PRINT!"); });
    print(moo);
    asm("MSR cpsr_c,#(0b11111)");// Enable IRQ
    SET_IRQ_EXCEP_HANDLER([](){ print("AN IRQ AFTER PRINT!"); });
    return 0;
}

