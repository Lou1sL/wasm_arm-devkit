#include "main.h"

int main(void){
    std::string arr = "Hello, World!";
    bool switcher = true;
    while(true){
        arr[0] = switcher ? '^' : 'H';
        arr[1] = switcher ? '_' : 'e';
        arr[2] = switcher ? '^' : 'l';
        arr[3] = switcher ? ' ' : 'l';
        switcher = !switcher;
        warm::cout << arr;
    }
    return 0;
}