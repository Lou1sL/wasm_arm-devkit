#include <cstring>
#include <cinttypes>

volatile uint8_t * const scr_buffer = (uint8_t *)0x001FF00;
namespace warm {
    static uint8_t warm_scr_ptr = 0;
    static void clear(){
        warm_scr_ptr = 0;
        for(std::size_t i=0; i<0x100; i++) scr_buffer[i] = ' ';
    }
    static void print(const char* str){
        size_t len = strlen(str);
        for(std::size_t i=0; i<len; i++){
            if(str[i] == '\n'){
                warm_scr_ptr += 0b00100000;
                warm_scr_ptr &= 0b11100000;
            }else{
                scr_buffer[warm_scr_ptr] = str[i];
                warm_scr_ptr++;
            }
        }
    }
};