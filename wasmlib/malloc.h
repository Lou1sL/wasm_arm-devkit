
#include <stdlib.h>
#include <cinttypes>

constexpr size_t HEAP_SIZE = 2000;
std::uint32_t heap[HEAP_SIZE];

struct heap_block_metadata {
    size_t size;
    int is_free;
    struct heap_block_metadata *next;
};
//struct heap_block_metadata *freeList=(void*)heap;


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

