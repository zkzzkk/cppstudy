#include <iostream>
#include "sales.h"
#include <fstream>
#include <cerrno>
#include <cstring>
#include <vector>
#include <string>

using namespace std;


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

}


int main()
{
    Sales b1("hehe", 12, 3.4), b2("hehe", 50, 1.8);
    const Sales b3("haha", 11, 4.4);
    Sales b4;

    Sales::print(cout, b1);
    Sales::print(cout, b2);
    Sales::print(cout, b1.combine(b2));
    Sales::print(cout, Sales::add(b1, b2));
    cout << b4.get_intrest() << endl;
    cout << "=========file test ==========" << endl;

    try {
        file_test();
    } catch (runtime_error exp) {
        cout << "main got runtime error : " << exp.what() << endl;
    }

    return 0;
}
