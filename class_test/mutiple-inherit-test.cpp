#include <iostream>
#include <string>

using namespace std;

class ZooAnimal {
public:
    ZooAnimal() = default;
    ZooAnimal(const string &name):m_name(name) {}
    ZooAnimal(const string &name, float age):m_name(name),m_age(age) {}

    void set_name(string name) {m_name = name;}
    void set_age(float age) {m_age = age;}

    friend ostream &operator<<(ostream &os, ZooAnimal &animal);
protected:
    string m_name;
    float m_age;
};
ostream &operator<<(ostream &os, ZooAnimal &animal)
{
    os << "name("<<animal.m_name<<") "<<"age("<<animal.m_age<<")";
}

class Bear: public ZooAnimal {
public:
    using ZooAnimal::ZooAnimal;
    Bear():weight(0.0) {}
    Bear(float wt):weight(wt) {}
protected:
    float weight;
};
class Endangerd {
public:
    Endangerd():level(0.0){}
    Endangerd(float lv):level(lv) {}

protected:
    float level;
};
class Panda final: public Bear, public Endangerd {
public:
    using Bear::Bear;
    using Endangerd::Endangerd;
    Panda()=default;
    Panda(float wt):Bear(wt),Endangerd(1.5) {}
    Panda(float wt, string bam):Bear(wt),Endangerd(1.5),bamboo(bam){}

private:
    string bamboo;
};


void multi_inherit_test()
{
    Panda panpan("panpan", 10);
    cout << panpan <<endl;
}
