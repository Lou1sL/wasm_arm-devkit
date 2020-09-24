
#include <stdlib.h>
#include <cinttypes>

constexpr size_t HEAP_SIZE = 100;
std::uint32_t heap[HEAP_SIZE];

struct block_info {
    struct block_info *prev;
    struct block_info *next;
    size_t block_size;
    bool unused;
};
struct block_info *meta_head = (block_info*)heap;

void heapInit(){
    meta_head->prev = nullptr;
    meta_head->next = nullptr;
    meta_head->block_size = HEAP_SIZE;
    meta_head->unused = true;
}

void createBlock(size_t size){
    
}

void mergeUnusedBlock(){
    struct block_info *blk = meta_head;
    while(blk->next != nullptr){
        if(blk->unused && blk->next->unused){
            blk->block_size += blk->next->block_size;
            blk->next = blk->next->next;
        }
        blk = blk->next;
    }
}

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

