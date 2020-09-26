
class TEST_CLASS {
public:
    TEST_CLASS();
    virtual ~TEST_CLASS();
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
    TEST_VIRTUAL();
    ~TEST_VIRTUAL();
    void TestVirtual();
};

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

TEST_CLASS::TEST_CLASS()       { print("BASE CONSTRUCTOR\n");   }
void TEST_CLASS::TestVirtual() { print("BASE TestVirtual()\n"); }
TEST_CLASS::~TEST_CLASS()      { print("BASE DESTRUCTOR\n");    }

TEST_VIRTUAL::TEST_VIRTUAL()    { print("DERIVED CONSTRUCTOR\n");   }
void TEST_VIRTUAL::TestVirtual(){ print("DERIVED TestVirtual()\n"); }
TEST_VIRTUAL::~TEST_VIRTUAL()   { print("DERIVED DESTRUCTOR\n");    }

void TestPolymorphism(){
    TEST_CLASS* base = new TEST_CLASS();
    TEST_VIRTUAL* derived = new TEST_VIRTUAL();
    
    TEST_CLASS* test;
    test = base;    test->TestVirtual();
    if(dynamic_cast<TEST_VIRTUAL*>(test) == nullptr) print("DOWN CAST FAILED!\n");
    else test->TestVirtual();
    test = derived; test->TestVirtual();
    if(dynamic_cast<TEST_VIRTUAL*>(test) == nullptr) print("DOWN CAST FAILED!\n");
    else test->TestVirtual();

    delete base;
    delete derived;
}