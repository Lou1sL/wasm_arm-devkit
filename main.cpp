#include "main.h"


const char moo[] = 
    "^__^               \n"
    "(oo)\\_______       \n"
    "(__)\\       )\\/\\   \n"
    "    ||----w |      \n"
    "    ||     ||      \n"
    "\n"
    "WELCOME TO WASM_ARM!\n";

int main(void){
    warm::print(moo, strlen(moo));
    return 0;
}