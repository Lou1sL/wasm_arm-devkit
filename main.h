#include "warmlib/warmlib.h"



class TEST_CLASS {
public:
    TEST_CLASS();
    virtual ~TEST_CLASS();
    int DumbFuncCall(uint32_t x, uint32_t y);
    void Moo();
    void TestInterrupt();
    virtual void TestVirtual();
private:
    const char moo[256] = 
        "^__^\n"
        "(oo)\\_______\n"
        "(__)\\       )\\/\\\n"
        "    ||----w |\n"
        "    ||     ||\n\n"
        "WELCOME TO WASM_ARM!!\n";
};

class TEST_VIRTUAL : public TEST_CLASS {
public:
    ~TEST_VIRTUAL();
    void TestVirtual();
};