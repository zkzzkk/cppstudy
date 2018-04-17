#ifndef SimpleTest_H
#define SimpleTest_H

#include <iostream>
#include <string>

class SimpleTest
{
public:
    SimpleTest() {std::cout << "SimpleTest's default construct" << std::endl;}
    SimpleTest(const std::string s): val(s) {std::cout << "SimpleTest's construct: " << s << std::endl;}
    SimpleTest(const char *s): SimpleTest(std::string(s)) {}

    SimpleTest(const SimpleTest &a): val(a.val) {std::cout << "SimpleTest's copy-construction called: " << val << std::endl;}
    SimpleTest(SimpleTest &&ra) noexcept: val(std::move(ra.val)) {
        std::cout << "SimpleTest's move-construction called: " << val <<std::endl;
        ra.val = val + "-moveout";
    }
    virtual ~SimpleTest() {std::cout << "SimpleTest's destructor: " << val << std::endl;}

    SimpleTest &operator=(const SimpleTest &ra) {val = ra.val; std::cout << "SimpleTest's copy-assignment called: " << val << std::endl; return *this;}
    SimpleTest &operator=(SimpleTest &&ra) noexcept {
        val = ra.val; std::cout << "SimpleTest's move-assignment called: " << val << std::endl;
        ra.val = val + "-moveout";
        return *this;
    }

    virtual void simple_virt() {std::cout << "simpleTest's virtual: " << val << std::endl;}
    void fun1() {std::cout << "simpleTest's func1: " << val << std::endl;}
    void fun1(int) {}

    friend inline std::ostream &operator<<(std::ostream &os, const SimpleTest &s);
protected:
    std::string val;
};

class SimpleTestInterface: public SimpleTest
{
public:
    SimpleTestInterface(const std::string v):SimpleTest(v){}
    virtual void simple_virt() override = 0;
};

class SimpleTestDerived1: public SimpleTestInterface
{
public:
    SimpleTestDerived1(const std::string v, const std::string v1):SimpleTestInterface(v), d1_val(v1) {std::cout << "SimpleTestDerived1's construct: " << v1 << std::endl;}
    virtual void simple_virt() override final {std::cout << "SimpleTestDerived1's virtual: " << d1_val << std::endl;}
    void fun1() {std::cout << "SimpleTestDerived1's func1: " << d1_val << std::endl;}

    virtual ~SimpleTestDerived1() {std::cout << "SimpleTestDerived1's destructor: " << d1_val << std::endl;}
    std::string d1_val;
};

class SimpleTestDerived2: public SimpleTestDerived1
{
public:
    SimpleTestDerived2(const std::string v, const std::string v1, const std::string v2):SimpleTestDerived1(v,v1),d2_val(v2) {std::cout << "SimpleTestDerived2's construct: " << v2 << std::endl;}
    virtual ~SimpleTestDerived2() {std::cout << "SimpleTestDerived2's destructor: " << d2_val << std::endl;}

    void fun1() {std::cout << "SimpleTestDerived2's func1: " << d2_val << std::endl;}
    std::string d2_val;
};

inline std::ostream &operator<<(std::ostream &os, const SimpleTest &s)
{
    os << "SimpleTest << " << s.val;
    return os;
}

void simple_test();

#endif // SimpleTest_H
