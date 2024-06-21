#include <iostream>

class A {
public:
    void func() { f(); }
    virtual void f() { std::cout << "A::f() called" << std::endl; }
};

class B : public A {
public:
    void f() override { std::cout << "B::f() called" << std::endl; }
};

class C : public B {
public:
    void f() override { std::cout << "C::f() called" << std::endl; }
};

int main() {
    A a;
    B b;
    C c;

    // 호출 결과 확인
    a.f();  // A::f() called
    b.f();  // B::f() called
    c.f();  // C::f() called
    a.func();  // A::f() called
    b.func();  // B::f() called
    c.func();  // C::f() called

    return 0;
}
