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
    ~SimpleTest() {std::cout << "SimpleTest's destructor: " << val << std::endl;}

    SimpleTest &operator=(const SimpleTest &ra) {val = ra.val; std::cout << "SimpleTest's copy-assignment called: " << val << std::endl; return *this;}
    SimpleTest &operator=(SimpleTest &&ra) noexcept {
        val = ra.val; std::cout << "SimpleTest's move-assignment called: " << val << std::endl;
        ra.val = val + "-moveout";
        return *this;
    }

    std::string val;
};

inline std::ostream &operator<<(std::ostream &os, const SimpleTest &s)
{
    os << "SimpleTest << " << s.val;
    return os;
}

#endif // SimpleTest_H
