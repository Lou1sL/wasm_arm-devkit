#include "main.h"

int main(void){
    char str[] = "\n0\n123456789ABCDEF\n";
    warm::print(str, strlen(str));
    return 0;
}