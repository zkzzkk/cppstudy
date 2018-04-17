#include "simpletestclass.h"


void simple_test()
{
    SimpleTestDerived2 d2("b","d1","d2");

    d2.simple_virt();
    SimpleTestDerived1 &rd1 = d2;
    rd1.fun1();
    rd1.simple_virt();
}
