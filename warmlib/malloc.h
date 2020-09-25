#include <cinttypes>

constexpr size_t BYTE_ALIGN = 4;
constexpr size_t HEAP_SIZE = 100;
char heap[HEAP_SIZE];

struct block_info {
    struct block_info *prev;
    struct block_info *next;
    size_t block_size;
    bool used;
} __attribute__ ((aligned (32)));
struct block_info *info_head = (block_info*)heap;

void infoHeadInit(){
    info_head->prev = nullptr;
    info_head->next = nullptr;
    info_head->block_size = HEAP_SIZE;
    info_head->used = false;
}

block_info* findUnusedBlock(block_info* from, size_t size_need){
    if(from == nullptr) return nullptr;
    else if((!from->used) && (from->block_size >= size_need)) return from;
    else return findUnusedBlock(from->next, size_need);
}

block_info* prepareUnusedBlock(size_t size_need){
    block_info* target_block = findUnusedBlock(info_head, size_need);
    if(target_block == nullptr) return nullptr;
    if(target_block->block_size <= (size_need + sizeof(block_info))) {
        //If the space left out can't even fit a info struct, then there is no need to create a new block anyway.
        target_block->used = true;
    }else{
        struct block_info *new_block = (block_info*)((block_info*)target_block + size_need);
        new_block->prev = target_block;
        new_block->next = target_block->next;
        new_block->block_size = target_block->block_size - size_need;
        new_block->used = false;

        target_block->next = new_block;
        target_block->block_size = size_need;
        target_block->used = true;
    }
    return target_block;
}

void mergeUnusedBlock(){
    struct block_info *block = info_head;
    while((block != nullptr) && (block->next != nullptr)){
        if((!block->used) && (!block->next->used)){
            block->block_size += block->next->block_size;
            block->next = block->next->next;
        }
        block = block->next;
    }
}

inline size_t align(size_t size){
    return size + (BYTE_ALIGN - size % BYTE_ALIGN);
}

bool initialized = false;

extern "C" void *malloc(size_t size) {
    if(!initialized) { infoHeadInit(); initialized = true; }
    //I hope block_info is properly aligned, I hope...
    size_t total_size = sizeof(block_info) + align(size);
    prepareUnusedBlock(total_size);
    return (void *)(block + sizeof(block_info));
}

extern "C" void free(void *ptr) {
    ((block_info*)ptr)->used = false;
    mergeUnusedBlock();
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

