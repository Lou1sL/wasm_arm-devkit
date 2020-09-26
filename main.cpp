
#include "main.h"

class A {
    public: virtual void foo(){ print("A foo()\n"); }
    virtual ~A(){}
};
class B : public A {
    public: virtual void foo(){ print("B foo()\n"); }
};

void testPoly(){
    A* a = new A();
    B* b = new B();
    A* aa;
    B* bb;

    aa = a; aa->foo();
    bb = dynamic_cast<B*>(aa);
    if(bb == nullptr) print("Down cast failed!\n");
    else bb->foo();

    aa = b; aa->foo();
    bb = dynamic_cast<B*>(aa);
    if(bb == nullptr) print("Down cast failed!\n");
    else bb->foo();

    delete a;
    delete b;
}

int main(void){

    testPoly();

    return 0;
}

//for(var i=0; i<0x20000; i++) if(SIM_memget(i) == 0x69) console.log(i.toString(16))