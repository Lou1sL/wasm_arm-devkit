
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
typedef int ARM_CBIT_LOCK;
static constexpr ARM_CBIT_LOCK ARM_CBIT_SYS_INT_DISABLE = 0b011011111;
static constexpr ARM_CBIT_LOCK ARM_CBIT_SYS_INT_ENABLE  = 0b000011111;

extern "C" ARM_CBIT_LOCK ARM_LOCK_CBIT(ARM_CBIT_LOCK lock);
extern "C" void ARM_UNLOCK_CBIT(ARM_CBIT_LOCK lock);

typedef void (*EXCEP_HANDLER)(void);
EXCEP_HANDLER h_und = [](){}, h_swi = [](){}, h_irq = [](){};
void SET_UND_EXCEP_HANDLER(EXCEP_HANDLER hn) { h_und = hn; }
void SET_SWI_EXCEP_HANDLER(EXCEP_HANDLER hn) { h_swi = hn; }
void SET_IRQ_EXCEP_HANDLER(EXCEP_HANDLER hn) { h_irq = hn; }

extern "C" void und_handler(void) {
    ARM_CBIT_LOCK lock = ARM_LOCK_CBIT(ARM_CBIT_SYS_INT_DISABLE);
    (*((EXCEP_HANDLER)h_und))();
    ARM_UNLOCK_CBIT(lock);
}
extern "C" void swi_handler(void) {
    ARM_CBIT_LOCK lock = ARM_LOCK_CBIT(ARM_CBIT_SYS_INT_DISABLE);
    (*((EXCEP_HANDLER)h_swi))();
    ARM_UNLOCK_CBIT(lock);
}
extern "C" void irq_handler(void) {
    ARM_CBIT_LOCK lock = ARM_LOCK_CBIT(ARM_CBIT_SYS_INT_ENABLE);
    (*((EXCEP_HANDLER)h_irq))();
    ARM_UNLOCK_CBIT(lock);
}