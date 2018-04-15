#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <map>
#include <utility>

using namespace std;

class A {
public:
    A()=default;
    A(int x): val(x) {cout << "A's default construct" << endl;}
    A(const A &a): val(a.val) {cout << "A's copy-construction called" << endl;}
    A(const A &&ra): val(ra.val) {cout << "A's move-construction called" << endl;}
    ~A() {cout << "A's destructor" << endl;}

    A &operator=(const A &ra) {val = ra.val; cout << "A's copy-assignment called" << endl; return *this;}
    A &operator=(const A &&ra) {val = ra.val; cout << "A's move-assignment called" << endl; return *this;}

    int val;
};
A get_A_copy()
{
    return A(12);
}
A &get_A_ref(A &a)
{
    a.val = 13;
    return a;
}
void _rval_test(A &&ra)
{
    A a1, a2;
    a1 = ra;
    a2 = std::move(ra);
}
void rvalue_test()
{
    A a, a2;
    cout << "get a copy, and assign========\n";
    a = get_A_copy();
    cout << "get a ref, and assign=======\n";
    a = get_A_ref(a);
    cout << "get a copy, and assign to a rref======\n";
    A &&ra = get_A_copy();
    a2 = std::move(ra);

    cout << "test using allocator\n";
    std::allocator<A> alloc;
    A *pa = alloc.allocate(2);
    alloc.construct(pa, a);
    alloc.construct(pa, std::move(ra));

    cout << "test rval with func call\n";
    _rval_test(std::move(a));

    cout << "function ends! ==================\n";
}


#include "myvec.h"

int main()
{
    //rvalue_test();
    test_myvec();
    return 0;
}
