#include "sales.h"
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <cerrno>
#include <cstring>

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
    if (m_isbn == "")
        m_isbn = data.isbn();

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

#include <iomanip>
std::ostream &Sales::print(std::ostream &os, const Sales &b)
{
    os << "isbn(" << setw(10) << b.isbn() << ") units(" << b.m_units << ") \tprice(" << b.m_price << ") \trevenue(" << b.m_revenue << ") \tavg_price(" << b.avg_prive() << ")" << std::endl;
    return os;
}

bool Sales::_less(const Sales &b, const std::string &field) const
{
    if (field == "isbn")
        return isbn() < b.isbn();
    if (field == "units")
        return m_units < b.m_units;
    if (field == "price")
        return m_price < b.m_price;
    if (field == "revenue")
        return m_revenue < b.m_revenue;
    if (field == "avg_price")
        return avg_prive() < b.avg_prive();

    return false;
}

bool Sales::_less(const Sales &x, const Sales &y, const std::string &field)
{
    return x._less(y, field);
}


//====================statistics==========================================================================================
std::ostream &Sales_statis::print(std::ostream &os)
{
    for (auto &b : m_statis) {
        Sales::print(os, b);
    }
    return os;
}

std::ostream &Sales_statis::print(std::ostream &os, const string isbn)
{
    for_each(m_statis.cbegin(), m_statis.cend(), [&isbn,&os](const Sales &book){ if (book.isbn() == isbn) book.print(os); });
    return os;
}

std::ostream &Sales_statis::print_map(std::ostream &os) const
{
    for(auto &item : m_map) {
        item.second.print(os);
    }
    return os;
}

std::ostream &Sales_statis::print_one_from_map(std::ostream &os, const std::string isbn)
{
    auto it = m_map.find(isbn);
    if (it != m_map.end())
        it->second.print(os);

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

    m_rawdata.push_back(book);

    //=========map version
#if 0
    auto ret = m_map.insert(make_pair(book.isbn(), book));
    if (!ret.second) {
        ret.first->second.combine(book);
    }
#else
    m_map[book.isbn()].combine(book);

#endif
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
bool Sales_statis::eq_lambda_version(const Sales_statis &stati) const
{
    if (stati.m_statis.size() != m_statis.size())
        return false;

    return equal(m_statis.cbegin(), m_statis.cend(),
          stati.m_statis.cbegin(),
          [](const Sales &x, const Sales &y) -> bool
          {
              return x.eq(y);
          });
}


int Sales_statis::readin(std::istream &is)
{
    string line;

    if (!is) {
        throw runtime_error("istream invalid");
        return -1;
    }
    Sales book;
    while (book.readin(is)) {
        add(book);
    }
    return 1;
}

int Sales_statis::readin(const string file)
{
    ifstream ifs;
    int ret;

    ifs.open(file, ifstream::in);
    if (!ifs) {
        string err = strerror(errno);
        throw runtime_error(err);
        return -1;
    }
    ret = readin(ifs);
    ifs.close();

    return ret;
}

void Sales_statis::sort_lambda_version(const std::string &field)
{
    auto my_less = [&field](const Sales &x, const Sales &y)->bool {return x._less(y, field);};

    return sort(m_statis.begin(), m_statis.end(), my_less);
}
#include <functional>
using std::placeholders::_1;
using std::placeholders::_2;
bool Sales::_less(const Sales &x, const Sales &y, const std::string &field);

void Sales_statis::sort_bind_version(const std::string &field)
{
    auto my_less = bind(static_cast<bool (*)(const Sales &, const Sales &, const std::string &)>(Sales::_less), _2, _1, field);

    sort(m_statis.begin(), m_statis.end(), my_less);
}



