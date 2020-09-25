#include "main.h"



class TEST_CLASS {
public:
    TEST_CLASS(){
        print("CONSTRUCTOR!\n");
        SET_UND_EXCEP_HANDLER([](){ print("EXCEP UND!\n"); });
        SET_SWI_EXCEP_HANDLER([](){ print("EXCEP SWI!\n"); });
    }

    ~TEST_CLASS(){
        print("DESTROYED!\n");
        SET_UND_EXCEP_HANDLER([](){});
        SET_SWI_EXCEP_HANDLER([](){});
    }
    int DumbFuncCall(uint32_t x, uint32_t y);
    void PrintMoo();
    void TestIRQ();
private:
    const char moo[256] = 
        "^__^\n"
        "(oo)\\_______\n"
        "(__)\\       )\\/\\\n"
        "    ||----w |\n"
        "    ||     ||\n\n"
        "WELCOME TO WASM_ARM!!\n";
};
int TEST_CLASS::DumbFuncCall(uint32_t x = 0x33443344, uint32_t y = 0x11221122){
    return 0x55665566;
}
void TEST_CLASS::PrintMoo(){
    print(this->moo);
}
void TEST_CLASS::TestIRQ(){
    print("IRQ ENABLED!\n");
    SET_IRQ_EXCEP_HANDLER([](){ print("IRQ BEFORE/DURING PRINT!\n"); });
    ARM_CBIT_LOCK lock = ARM_LOCK_CBIT(ARM_CBIT_SYS_INT_ENABLE);
    print("I'm PRINT!\n");
    ARM_UNLOCK_CBIT(lock);
    SET_IRQ_EXCEP_HANDLER([](){ print("IRQ AFTER PRINT!\n"); });
    lock = ARM_LOCK_CBIT(ARM_CBIT_SYS_INT_ENABLE);
    print("I'm AFTER PRINT!\n");
    ARM_UNLOCK_CBIT(lock);
    print("IRQ DISABLED!\n");
}

int main(void){
    TEST_CLASS* test = new TEST_CLASS();
    __attribute__((unused))
    int a = test->DumbFuncCall();
    test->PrintMoo();
    test->TestIRQ();
    delete test;
    return 0;
}

//for(var i=0; i<0x20000; i++) if(SIM_memget(i) == 0x69) console.log(i.toString(16))