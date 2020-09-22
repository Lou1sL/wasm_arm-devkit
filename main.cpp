#include "main.h"


const char moo[] = 
    "^__^\n"
    "(oo)\\_______\n"
    "(__)\\       )\\/\\\n"
    "    ||----w |\n"
    "    ||     ||\n\n"
    "WELCOME TO WASM_ARM!!\n";

int main(void){
    SET_UND_EXCEP_HANDLER([](){ print("UND!\n"); });
    SET_SWI_EXCEP_HANDLER([](){ print("SWI!\n"); });

    SET_IRQ_EXCEP_HANDLER([](){ print("IRQ BEFORE/DURING PRINT!\n"); });
    asm("MSR cpsr_c,#(0b11111)");// Enable IRQ
    print(moo);
    SET_IRQ_EXCEP_HANDLER([](){ print("IRQ AFTER PRINT!\n"); });
    asm("MSR cpsr_c,#(0b11111)");// Enable IRQ
    while(1){}
    return 0;
}

