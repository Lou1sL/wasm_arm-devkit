#include "main.h"

int TEST_CLASS::DumbFuncCall(uint32_t x = 0x33443344, uint32_t y = 0x11221122){
    return 0x55665566;
}
void TEST_CLASS::Moo(){
    print(this->moo);
}
void TEST_CLASS::TestInterrupt(){
    SET_UND_EXCEP_HANDLER([](){ print("EXCEP UND!\n"); });
    SET_SWI_EXCEP_HANDLER([](){ print("EXCEP SWI!\n"); });
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
    SET_UND_EXCEP_HANDLER([](){});
    SET_SWI_EXCEP_HANDLER([](){});
}
void TEST_CLASS::TestVirtual()  { print("I'm BASE!\n");    }
void TEST_VIRTUAL::TestVirtual(){ print("I'm DERIVED!\n"); }

TEST_CLASS::TEST_CLASS()     { print("BASE CONSTRUCTOR!\n");  }
TEST_CLASS::~TEST_CLASS()    { print("BASE DESTROYED!\n");    }
TEST_VIRTUAL::~TEST_VIRTUAL(){ print("DERIVED DESTROYED!\n"); }

int main(void){

    TEST_CLASS* base = new TEST_CLASS();
    TEST_VIRTUAL* derived = new TEST_VIRTUAL();
    //__attribute__((unused))
    //int a = test_base->DumbFuncCall();
    //test_base->Moo();
    //test_base->TestInterrupt();
    


    TEST_CLASS* test = base;
    test->TestVirtual();
    test = derived;
    test->TestVirtual();
    TEST_VIRTUAL* test2 = dynamic_cast<TEST_VIRTUAL*>(test);
    if(test2 == nullptr) print("DOWNCAST FAILED!\n");
    else test2->TestVirtual();

    delete base;
    delete derived;
    return 0;
}

//for(var i=0; i<0x20000; i++) if(SIM_memget(i) == 0x69) console.log(i.toString(16))