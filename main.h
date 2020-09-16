#include <cstring>
#include <cinttypes>

volatile uint8_t * const scr_buffer = (uint8_t *)0x001FF00;
namespace warm {
    static uint8_t warm_scr_ptr = 0;
    static void print(const char* str, size_t sz){
        for(std::size_t i=0; i<sz; i++){
            scr_buffer[warm_scr_ptr] = str[i];
            warm_scr_ptr++;
        }
    }
};