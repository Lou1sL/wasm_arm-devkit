
#include <cinttypes>

typedef std::uint32_t ARM_CBIT_LOCK;
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