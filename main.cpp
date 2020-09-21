#include "main.h"


const char moo[] = 
    "^__^\n"
    "(oo)\\_______\n"
    "(__)\\       )\\/\\\n"
    "    ||----w |\n"
    "    ||     ||\n\n"
    "WELCOME TO WASM_ARM!!\n";

int main(void){
    warm::print(moo);
    return 0;
}

extern "C" void und_handler(void) { warm::print("UND EXCEPTION TRIGGERED\n"); for (;;) { } }
extern "C" void swi_handler(void) { warm::print("SWI EXCEPTION TRIGGERED\n"); for (;;) { } }
extern "C" void irq_handler(void) { warm::print("IRQ EXCEPTION TRIGGERED\n"); for (;;) { } }