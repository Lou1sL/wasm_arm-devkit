
/* Standard Mem */
#include <stdlib.h>

extern "C" void *malloc(size_t) { 
    return (void *)0;
}
extern "C" void free(void *) {
    
}
void *operator new(size_t size) throw() {
    return malloc(size);
}
void operator delete(void *p) throw() {
    free(p);
}
extern "C" int __aeabi_atexit(void *object, void (*destructor)(void *), void *dso_handle) { 
    return 0;
}

/* Basic Output */
#include <cstring>
#include <cinttypes>
volatile uint8_t * const scr_buffer = (uint8_t *)0x001FF00;
uint8_t warm_scr_ptr = 0;
void clear(){
    warm_scr_ptr = 0;
    for(std::size_t i=0; i<0x100; i++){
        scr_buffer[i] = 0x20;
    }
}
void print(const char* str){
    size_t len = strlen(str);
    for(std::size_t i=0; i<len; i++){
        if(str[i] == '\n' || str[i] == '\r'){
            warm_scr_ptr = (warm_scr_ptr + 0b00100000) & 0b11100000;
        }else{
            scr_buffer[warm_scr_ptr++] = str[i];
        }
    }
}

/* Exception */
#define ARM_INT_LOCK int
extern "C" ARM_INT_LOCK lock_interrupt(void);
extern "C" void unlock_interrupt(ARM_INT_LOCK lock);

typedef void (*EXCEP_HANDLER)(void);
EXCEP_HANDLER h_und = [](){}, h_swi = [](){}, h_irq = [](){};
void SET_UND_EXCEP_HANDLER(EXCEP_HANDLER hn) { h_und = hn; }
void SET_SWI_EXCEP_HANDLER(EXCEP_HANDLER hn) { h_swi = hn; }
void SET_IRQ_EXCEP_HANDLER(EXCEP_HANDLER hn) { h_irq = hn; }

extern "C" void und_handler(void) {
    ARM_INT_LOCK lock = lock_interrupt();
    (*((EXCEP_HANDLER)h_und))();
    unlock_interrupt(lock);
}
extern "C" void swi_handler(void) {
    ARM_INT_LOCK lock = lock_interrupt();
    (*((EXCEP_HANDLER)h_swi))();
    unlock_interrupt(lock);
}
extern "C" void irq_handler(void) {
    EXCEP_HANDLER handler = (EXCEP_HANDLER)h_irq;
    asm("MSR cpsr_c,#(0b11111)");// Enable IRQ
    (*handler)();
    asm("MSR cpsr_c,#(0b11111 | 0b10000000)");// Disable IRQ
}