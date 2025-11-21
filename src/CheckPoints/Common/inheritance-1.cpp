////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @brief   Testing of understanding a C++ inheritance mechanism
/// @details Look into unit-tests and predict the console output each of them
/// @author  Alexey Perestoronin: aperestoronin@aligntech.com
/// @date    22.10.2022
///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <gtest/gtest.h>

struct A {
    A() {
        std::cout << "\nA::A";
    }
    virtual ~A() {
        std::cout << "\n~A::A";
    }
};

struct B : A {
    B() {
        std::cout << "\nB::B";
    }
    ~B() {
        std::cout << "\n~B::B";
    }
};

struct C : B {
    C() {
        std::cout << "\nC::C";
    }
    ~C() {
        std::cout << "\n~C::C";
    }
};

TEST(Inheritance1, Test1) {
    A* ptr = new C{};
    delete ptr;

    std::cout << std::endl;
}

TEST(Inheritance1, Test2) {
    B* ptr = new C{};
    delete ptr;

    std::cout << std::endl;
}

TEST(Inheritance1, Test3) {
    C* ptr = new C{};
    delete ptr;

    std::cout << std::endl;
}