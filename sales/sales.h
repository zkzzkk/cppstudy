#ifndef SALES_H_INCLUDED
#define SALES_H_INCLUDED

#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <map>

class Sales
{
public:
    typedef std::string::size_type pos;

    Sales(const std::string &isbn, int units, double price):
        m_isbn(isbn), m_units(units), m_revenue(price * units), m_price(price) {}
    Sales() = default;
    Sales(const std::string &isbn);

    const std::string &isbn() const;
    Sales &combine(const Sales &data);
    bool _less(const Sales &b, const std::string &field) const;
    static bool _less(const Sales &x, const Sales &y, const std::string &field);
    void set_revenue(double revenue) {m_revenue = revenue;}

    void access() const {++m_access_cnt;}
    static double get_intrest() {return intrestRate;}

    //compare
    bool eq(const Sales &book) const
    {
        if (book.m_isbn != m_isbn) return false;
        if (book.m_units != m_units) return false;
        if (book.m_revenue != m_revenue) return false;
        if (book.m_price != m_price) return false;
        return true;
    }

    std::istream &readin(std::istream &is);
    std::ostream &print(std::ostream &os) const {return print(os, *this);};
    //helper
    static std::ostream &print(std::ostream &os, const Sales &b);
    static Sales add(const Sales &b1, const Sales &b2);

private:
    std::string m_isbn;
    int m_units;
    double m_revenue;
    double m_price;
    mutable unsigned long long m_access_cnt = 0;
    static double intrestRate;
    static double initIntrest() {return 4.19;}

    double avg_prive() const {return m_units ? m_revenue/m_units : 0;}
    void init_revenue() {m_revenue = m_price * m_units;}
};


class Sales_statis {
public:
    Sales_statis() = default;
    Sales_statis(std::string file) {readin(file);}

    ~Sales_statis() {std::cout << "deconstruct!! 0x" << this << std::endl;}

    std::ostream &print(std::ostream &os);
    std::ostream &print(std::ostream &os, const std::string isbn);
    std::ostream &print_raw(std::ostream &os) const {return do_print(os, m_rawdata);}
    std::ostream &print_map(std::ostream &os) const;
    std::ostream &print_one_from_map(std::ostream &os, const std::string isbn);

    int add(const Sales &book);
    int add(const std::string &str);
    bool eq(const Sales_statis &stati) const;
    bool eq_lambda_version(const Sales_statis &stati) const;
    void sort_lambda_version(const std::string &field);
    void sort_bind_version(const std::string &field);


    int readin(std::istream &is);
    int readin(const std::string file);

private:
    std::vector<Sales> m_statis;
    std::list<Sales> m_rawdata;
    std::map<std::string, Sales> m_map;

    template <class _InputIterator>
    std::ostream &do_print(std::ostream &os, _InputIterator &_first, _InputIterator &_last) const;
    template <class Container>
    std::ostream &do_print(std::ostream &os, const Container &c) const;
};

template <class Container>
std::ostream &Sales_statis::do_print(std::ostream &os, const Container &c) const
{
    for (auto &b : c) {
        Sales::print(os, b);
    }
    return os;
}

template <class _InputIterator>
std::ostream &Sales_statis::do_print(std::ostream &os, _InputIterator &_first, _InputIterator &_last) const
{
    while(_first != _last) {
        Sales::print(os, *_first);
        ++_first;
    }
    return os;
}
#endif // SALES_H_INCLUDED
