#ifndef SALES_H_INCLUDED
#define SALES_H_INCLUDED

#include <string>
#include <iostream>
#include <vector>

class Sales
{
public:
    typedef std::string::size_type pos;

    Sales(const std::string &isbn, int units, double price):
        m_isbn(isbn), m_units(units), m_revenue(price * units), m_price(price) {}
    Sales(): Sales("dumy", 1, 1){}
    Sales(const std::string &isbn);

    const std::string &isbn() const;
    Sales &combine(const Sales &data);
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

    double avg_prive() {return m_units ? m_revenue/m_units : 0;}
    void init_revenue() {m_revenue = m_price * m_units;}
};


class Sales_statis {
public:
        std::ostream &print(std::ostream &os);
        int add(const Sales &book);
        int add(const std::string &str);
        bool eq(const Sales_statis &stati) const;


private:
    std::vector<Sales> m_statis;
};

#endif // SALES_H_INCLUDED
