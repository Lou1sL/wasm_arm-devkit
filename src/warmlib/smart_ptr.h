/**
 * This is a simple implementaion of C++'s unique_ptr and shared_ptr for WASM_ARM.
 * No Exception support and only for single-thread usage.
 * 
 */

class ReferenceCounter {
private:
    int count;
public:
    void Add(){ count++; }
    int Sub(){ return --count; }
};


template<class T>
class unique_ptr {
private:
    T* ptr;
    ReferenceCounter* rc;
public:
    unique_ptr()     : ptr(nullptr), rc(nullptr) { rc = new ReferenceCounter(); rc->Add(); }
    unique_ptr(T* p) : ptr(p)                    { rc = new ReferenceCounter(); rc->Add(); }
    unique_ptr(const unique_ptr<T>& up) : ptr(up.ptr), rc(up.rc) { rc->Add(); }
    ~unique_ptr() { if(rc->Sub() == 0){ delete ptr; delete rc; } }
    T& operator*() { return *ptr; }
    T* operator->() { return ptr; }
    unique_ptr<T>& operator=(const unique_ptr<T>& up){
        if(this != &up){
            //Since nullptr check is already performed inside malloc.h's free(), there's no need to check here.
            if(rc->Sub() == 0){ delete ptr; delete rc; }
            ptr = up.ptr;
            rc = up.rc;
            rc->Add();
        }
        return *this;
    }
    void reset(){

    }
};

template<class T>
class shared_ptr {

};