#include "simpletestclass.h"
#include <iostream>

using namespace std;

void simple_test()
{
    SimpleTestDerived2 d2("b","d1","d2");

    d2.simple_virt();
    SimpleTestDerived1 &rd1 = d2;
    rd1.fun1();
    rd1.simple_virt();

    cout << "===========using construct inherited from base==========>" << endl;
    SimpleTestDerived2 d2_2("hehe");

    cout << "===========test function finished =============>"<<endl;
}
