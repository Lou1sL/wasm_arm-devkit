
#include "main.h"


class A{
public:
    virtual int Foo() { return 0; }
};

class B : public A {
public:
    int Foo() { return 2; }
};

int main() {
    A* a = new B();
    B* b = dynamic_cast<B*>(a);

    return 0;
} 