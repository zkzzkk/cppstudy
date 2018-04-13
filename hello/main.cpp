#include <iostream>
#include <cctype>
#include <vector>
#include <string>

using namespace std;

struct Sales_data
{
    std::string name{"haha"};
    int sold = 0;
    double price{0};
};

int my_echo()
{
    string str;

    while (cin >> str)
    {
        cout << str << endl;
    }
    return 0;
}

void my_toupper(string &str)
{
    for(auto &c : str)
    {
        c = toupper(c);
    }
}

template <typename T>
void my_vector_dump(T &v)
{
    for (auto &c : v)
    {
        cout << c << " ";
    }
    cout << endl;
}

template <typename T>
void my_vec_input(vector<T> &v)
{
    T c;

    while (cin >> c) {
        v.push_back(c);
    }
    cout << endl;
}

void my_vector_test()
{
    vector<int> va(5, 3);
    vector<string> vs1;

    my_vec_input(vs1);
    for (auto &s : vs1) {
        if (s.empty())
            continue;
        for (auto &c : s) {
            c = toupper(c);
        }
    }
    my_vector_dump(vs1);

    va = {1,2,3,4,5,6,7,8};
    my_vector_dump(va);
}

int constexpr get_size()
{
    return 5;
}

void test_array()
{
    int a[get_size()]{3};

    my_vector_dump(a);
}

void case_test()
{
    unsigned long va = 0x12334455UL;
    int *ptr;
    int pa;

    pa = static_cast<int>(va);
    ptr = reinterpret_cast<int *>(va);
}

void exception_test()
{
    int a, b;
    while (cin >> a >> b) {

        try {
            float f = static_cast<float>(a)/b;

            if (a == b) {
                throw runtime_error("they cannot be the same\n");
            }

            cout << f << endl;
        } catch (runtime_error &e) {
            cout << "runtime" << e.what() << endl;
        } catch (exception exp){
            cout << "exception" << exp.what() << endl;
        }

    }
}

template <typename T>
void initializer_test(initializer_list<T> il)
{
    for (const T &elem : il)
        cout << elem << endl;
}

int main()
{

    //my_echo();
    //my_vector_test();
    //test_array();
    //exception_test();
    initializer_test({1,2,3,5,6});

    cout << "Hello world!" << endl;
    return 0;
}
