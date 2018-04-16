#include <iostream>
#include "sales.h"
#include <fstream>
#include <cerrno>
#include <cstring>
#include <vector>
#include <string>
#include <memory>

using namespace std;


void sales_test()
{
    Sales b1("hehe", 12, 3.4), b2("hehe", 50, 1.8);
    const Sales b3("haha", 11, 4.4);
    Sales b4;

    Sales::print(cout, b1);
    Sales::print(cout, b2);
    Sales::print(cout, b1.combine(b2));
    Sales::print(cout, Sales::add(b1, b2));
    cout << b4.get_intrest() << endl;
}

void file_test()
{
    ifstream ifs;
    string line;
    Sales_statis stati;
    Sales_statis stati2;

    ifs.open("sales_data.txt", ifstream::in);
    if (!ifs) {
        string err = strerror(errno);
        throw runtime_error(err);
    }
    //getline(ifs, line);
    //cout << line << endl;

    Sales book;
    while (book.readin(ifs)) {
        stati.add(book);
    }
    stati.print(cout);

    ifs.clear();
    ifs.seekg(std::ios_base::beg);
    while (getline(ifs, line)) {
        stati2.add(line);
    }
    stati2.print(cout);
    cout << "statistics equal ? " << stati2.eq(stati) << endl;
    stati2.add("hehe		50		1");
    cout << "statistics equal too ? " << stati2.eq(stati) << endl;

}

void lambda_test()
{
    Sales_statis statis;

    statis.readin("sales_data.txt");

    cout << "all statis ============>" << endl;
    statis.print(cout);
    cout << "hehe book statis ==========>" << endl;
    statis.print(cout, "hehe");
    cout << "sort by avg prices ==========>" << endl;
    statis.sort_lambda_version("avg_price");
    statis.print(cout);
    cout << "sort by avg units ==========>" << endl;
    statis.sort_bind_version("units");
    statis.print(cout);
}

shared_ptr<Sales_statis> get_a_statis()
{
    shared_ptr<Sales_statis> sp(new Sales_statis("sales_data.txt"));

    return sp;
}

void share_ptr_test()
{
    auto sp = get_a_statis();
    shared_ptr<Sales_statis> sp2 = sp;

    cout << "is sp uniqe? " << sp2.unique() << endl;
    sp->print(cout);

    cout << "sp3 from sales2 ==============>" << endl;
    auto sp3 = make_shared<Sales_statis>(("sales_data2.txt"));
    sp3->print(cout);

    cout << "reset sp to sp3" << endl;
    sp = sp3;
    cout << "reset sp2 to nullptr" << endl;
    sp2.reset(static_cast<Sales_statis*>(nullptr));

    cout << "function returns\n";
}


void map_test()
{
    Sales_statis statis("sales_data.txt");

    cout << "raw ==========>" << endl;
    statis.print_raw(cout);

    cout << "all statis ============>" << endl;
    statis.print(cout);
    cout << "all statis in map ============>" << endl;
    statis.print_map(cout);
    cout << "haha statis in map ============>" << endl;
    statis.print_one_from_map(cout, "haha");
    statis.print_one_from_map(cout, "hh");

}

class A {
public:
    A() { cout << "create A 0x" << this << endl;}
    A(const A &a) {cout << "call A's copy-constructor 0x" << this << endl;}
    A& operator=(const A &a) {cout << "call A's operator= 0x" << this << endl; return *this;}
    virtual ~A() {cout << "destroy A 0x" << this << endl;}
    int a;
};

class AA : public A {
public:
    AA() { cout << "create AA 0x" << this << endl;}
    virtual ~AA() {cout << "destroy AA 0x" << this << endl;}
    int aa;
};

void delete_test()
{
    cout << "new A[3]" << endl;
    A *pa = new A[3];
    cout << "delete [] A[3]" << endl;
    delete [] pa;

    cout << "new A[3]" << endl;
    pa = new A[3];
    cout << "delete A[3]" << endl;
    delete pa;

    cout << "new AA" << endl;
    pa = new AA;
    cout << "convert AA* to A*, then delete it" << endl;
    delete pa;

    cout << "new AA[3]" << endl;
    pa = new AA[3];
    cout << "convert AA* to A*, then delete [] it" << endl;
    delete [] pa;
}

void allocator_test()
{
    allocator<A> a;
    cout << "a.allocate" << endl;
    A *p = a.allocate(3);

    cout << "a0.construct" << endl;
    a.construct(p);

    cout << "fill a1 a2 ==>" <<endl;
    uninitialized_fill_n(p+1, 2, A());

    cout << "using std::copy ==>" << endl;
    A arr[2];
    copy(arr, arr+2, p);

    cout << "destroy A[3]" <<endl;
    for (int i=2; i>=0; i--)
        a.destroy(p+i);

    cout << "deallocate it" <<endl;
    a.deallocate(p, 3);

}

#include "mygrep.h"

int main()
{
    try {
        //sales_test();
        //file_test();
        //lambda_test();
        //map_test();
        //share_ptr_test();
        //delete_test();
        //allocator_test();
        mygrep_test();
    } catch (runtime_error exp) {
        cout << "main got runtime error : " << exp.what() << endl;
    } catch (exception exp) {
        cout << "main got exption : " << exp.what() <<endl;
    }

    return 0;
}
