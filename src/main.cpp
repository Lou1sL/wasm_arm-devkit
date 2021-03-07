
#include "main.h"


int num = 1;
int IAmRecursion(int i){
    return (i <= 100000) ? IAmRecursion(i + num) : i;
}
int main(void){
    return IAmRecursion(0);
}