#include "myvec.h"
#include "simpletestclass.h"

using namespace std;

template<typename T>
std::allocator<T> MyVec<T>::m_alloc;

void test_myvec_string()
{
    MyVec<string> vec;

    vec.push_back("hehe");
    vec.push_back("hh");
    vec.push_back("tt");
    vec.push_back("fdsafd");
    vec.push_back("trdfsa");

    cout << vec << endl;
}

template<typename T>
void _test_myvec()
{
    MyVec<T> vec, vec2, vec3;

    vec.push_back(string("hehe"));
    vec.push_back("hoho");
    vec.push_back("haha");
    cout << vec << endl;

    cout << "======= copy vec1 to vec2===============>\n";
    vec2 = vec;
    cout << vec2 << endl;

    cout << "======= move vec2 to vec3===============>\n";
    vec3 = std::move(vec2);
    cout << vec3 << endl;
    vec2.push_back("hehe");
    vec2.push_back("hoho");
    cout << vec2 << endl;

    cout << "======= is v1 == v3? should be 1: " << (vec == vec3) << endl;
    cout << "======= is v1 == v2? should be 0: " << (vec == vec2) << endl;
    cout << "======= vec[1] =" << vec[1] << endl;

    cout << "========== after all test ===========>\n";
}

void test_myvec()
{
    _test_myvec<string>();
}

