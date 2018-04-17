#ifndef MYVEC_H
#define MYVEC_H
#include <memory>
#include <string>
#include <iostream>
#include <cstring>

template<typename T>
class MyVec
{
public:
    typedef std::size_t size_type;
    typedef T *iterator;
    typedef const T *const_iterator;

    MyVec();
    virtual ~MyVec();
    MyVec(const MyVec& other);
    MyVec(MyVec&& other);

    MyVec& operator=(const MyVec& other);
    MyVec<T>& operator=(MyVec<T>&& rhs);

    size_type size() const {return m_last - m_first;}
    size_type caps() const {return m_cap - m_first;}
    void push_back(const T &elem);
    void push_back(T &&elem);

    const_iterator begin() const {return m_first;}
    const_iterator end() const {return m_last;}
    iterator begin() {return m_first;}
    iterator end() {return m_last;}
    const_iterator cbegin() const {return m_first;}
    const_iterator cend() const {return m_last;}

    const T &operator[](size_type n) const
    {
        return m_first[n];
    }
    T &operator[](size_type n)
    {
        return m_first[n];
    }

    //just for test, bad example
    explicit operator bool() const {return size();}

protected:

private:
    T *m_first;
    T *m_last;
    T *m_cap;
    static std::allocator<T> m_alloc;

    void check_realloc_n(size_type n);
    void do_free();
};

template<typename T>
MyVec<T>::MyVec():
    m_first(nullptr), m_last(nullptr), m_cap(nullptr)
{
}

template<typename T>
MyVec<T>::~MyVec()
{
    do_free();
}

template<typename T>
MyVec<T>::MyVec(const MyVec& other): MyVec()
{
    check_realloc_n(other.size());
    std::uninitialized_copy(other.begin(), other.end(), begin());
    m_last = m_first + (other.size());
}

template<typename T>
MyVec<T>::MyVec(MyVec&& other)
{
    m_first = other.m_first;
    m_last = other.m_last;
    m_cap = other.m_cap;
    other.m_first = other.m_last = other.m_cap = nullptr;
}

template<typename T>
MyVec<T>& MyVec<T>::operator=(const MyVec<T>& rhs)
{
    if (this == &rhs) return *this; // handle self assignment

    do_free();
    check_realloc_n(rhs.size());
    std::uninitialized_copy(rhs.begin(), rhs.end(), begin());
    m_last = m_first + (rhs.size());

    return *this;
}

template<typename T>
MyVec<T>& MyVec<T>::operator=(MyVec<T>&& other)
{
    if (this == &other) return *this; // handle self assignment

    do_free();
    m_first = other.m_first;
    m_last = other.m_last;
    m_cap = other.m_cap;
    other.m_first = other.m_last = other.m_cap = nullptr;

    return *this;
}

template<typename T>
std::ostream &operator<<(std::ostream &os, const MyVec<T> &vec)
{
    os << vec.size() << " elements of caps " << vec.caps() << " are =======>>>" << std::endl;
    for (auto &i : vec) {
        os << i << std::endl;
    }
    return os;
}

template<typename T>
void MyVec<T>::push_back(const T &elem)
{
    check_realloc_n(1);
    m_alloc.construct(m_last++, std::move(elem));
}

template<typename T>
void MyVec<T>::push_back(T &&elem)
{
    check_realloc_n(1);
    m_alloc.construct(m_last++, std::move(elem));
}

template<typename T>
void MyVec<T>::check_realloc_n(size_type n)
{
    size_type oldsize = size();
    size_type needed = oldsize + n;

    if (caps() >= needed)
        return;

    size_type realloc = caps() ? caps() : 1;
    while (realloc < needed)
        realloc *= 2;

    //realloc a memory
    T *p = m_alloc.allocate(realloc);
    iterator dst = p;
    for(iterator i=begin(); i!=end(); ++i, ++dst) {
        m_alloc.construct(dst, std::move(*i));
    }
    do_free();

    m_first = p;
    m_last = dst;
    m_cap = p + realloc;
}


template<typename T>
void MyVec<T>::do_free()
{
    if (!size()) return;
    //deconstruct
    for(size_type i = size(); i != 0; --i) {
        m_alloc.destroy(m_first + i - 1);
    }
    m_alloc.deallocate(m_first, caps());
    m_first = m_last = m_cap = nullptr;
}

//============================operators ====================
template<typename T>
bool operator==(const MyVec<T> &a, const MyVec<T> &b)
{
    if (a.size() != b.size()) return false;
    for(typename MyVec<T>::const_iterator ia = a.cbegin(), ib = b.cbegin();
        ia != a.end(); ++ia, ++ib) {
        if (!(*ia == *ib))
            return false;
    }
    return true;
}
template<typename T>
bool operator!=(const MyVec<T> &a, const MyVec<T> &b)
{
    return !(a == b);
}



//testing function
void test_myvec();

#endif // MYVEC_H
