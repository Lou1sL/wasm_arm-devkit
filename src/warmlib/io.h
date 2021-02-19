
#include <cstring>
#include <cinttypes>
#include <utility>

volatile uint8_t* const scrout = (uint8_t*)0x01FFFF00;
size_t const SCR_SIZE = 0x100;

uint8_t warm_scr_ptr = 0;
void clear(){
    warm_scr_ptr = 0;
    for(std::size_t i=0; i<SCR_SIZE; i++){
        scrout[i] = 0x20;
    }
}
void print(const char* str, size_t size){
    for(std::size_t i=0; i<size; i++){
        if(str[i] == '\n' || str[i] == '\r'){
            warm_scr_ptr = (warm_scr_ptr + 0b00100000) & 0b11100000;
        }else{
            scrout[warm_scr_ptr++] = str[i];
        }
    }
}
void print(const char* str){
    print(str, strlen(str));
}
//class ScrBuffer : public std::stringbuf {
//public:
//    virtual int sync() {
//        print(this->str().c_str());
//        this->str("");
//    }
//};
//ScrBuffer buffer;
//void redirect_cout(){
//    std::ostream scr_stream(&buffer);
//    std::cout.rdbuf(scr_stream.rdbuf());
//}




void print(const char c){
    print(&c, 1);
}
void print(size_t num, size_t base = 10){
    int digits = 0;
    size_t n = num;
    do { n /= base; digits++; } while (n != 0);
    int d = digits - 1;
    do{
        size_t mod = num % base;
        if(mod >= 10) scrout[warm_scr_ptr+d] = 'A' + (mod - 10);
        else scrout[warm_scr_ptr+d] = '0' + mod;
        num /= base;
        d--;
    }while(num!=0);
    warm_scr_ptr += digits;
}

void print(long unsigned int num, size_t base = 10){
    print((size_t)num, base);
}