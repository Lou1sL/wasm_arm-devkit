#include "main.h"

int main(void){
    char str[] = 
        "^__^                  \n"
        "(oo)\\_______          \n"
        "(__)\\       )\\/\\      \n"
        "    ||----w |         \n"
        "    ||     ||         \n"
        "\n"
        "123456789ABCDEF\n";
    
    warm::print(str, strlen(str));
    return 0;
}