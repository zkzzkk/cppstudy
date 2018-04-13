#include "sales.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

double Sales::intrestRate = initIntrest();

Sales::Sales(const std::string &isbn):m_isbn(isbn)
{
    m_price = 0;
    m_units = 0;
    m_revenue = 0;
}

const std::string &Sales::isbn() const
{
    return m_isbn;
}
Sales &Sales::combine(const Sales &data)
{
    if (m_isbn != data.m_isbn)
        return *this;
    m_units += data.m_units;
    m_revenue += data.m_revenue;
    m_price = m_revenue / m_units;
    return *this;
}

Sales Sales::add(const Sales &b1, const Sales &b2)
{
    Sales tmp(b1);
    return tmp.combine(b2);
}

std::istream &Sales::readin(std::istream &is)
{
    is >> m_isbn >> m_units >> m_price;
    init_revenue();
    return is;
}

std::ostream &Sales::print(std::ostream &os, const Sales &b)
{
    os << "isbn(" << b.isbn() << ") units(" << b.m_units << ") price(" << b.m_price << ") revenue(" << b.m_revenue << ")" << std::endl;
    return os;
}

//====================static===============
std::ostream &Sales_statis::print(std::ostream &os)
{
    for (auto &b : m_statis) {
        Sales::print(os, b);
    }
    return os;
}

int Sales_statis::add(const Sales &book)
{
    auto b = m_statis.begin();

    for (; b != m_statis.end(); ++b) {
        if (b->isbn() == book.isbn()) {
            b->combine(book);
            break;
        }
    }
    if (b == m_statis.end())
        m_statis.push_back(book);

    return 0;
}

int Sales_statis::add(const string &str)
{
    istringstream istr(str);
    Sales book;

    if(!book.readin(istr)) {
        cerr << "error to parse:" << str << endl;
        throw runtime_error("file error!");
    }
    add(book);
    return 0;
}

bool Sales_statis::eq(const Sales_statis &stati) const
{
    auto i = m_statis.begin();
    auto j = stati.m_statis.begin();

    for ( ; i != m_statis.end() && j!=stati.m_statis.end(); ++i, ++j) {
        if (!i->eq(*j))
            return false;
    }
    if (i != m_statis.end() || j!=stati.m_statis.end())
        return false;

    return true;
}


