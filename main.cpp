#include "main.h"

int main(void){
    char str[] = "0123456789ABCDEF";
    for(int i=0; i<16; i++) warm::print(str, strlen(str));
    return 0;
}