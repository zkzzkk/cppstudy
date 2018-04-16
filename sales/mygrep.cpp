#include "mygrep.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

MyGrep::MyGrep():
    m_lines(new std::vector<std::string>)
{
}

MyGrep::~MyGrep()
{
    //dtor
}


int MyGrep::addline(const std::string &line)
{
    m_lines->push_back(line);
    int line_nr = m_lines->size() - 1;

    istringstream is(line);
    string word;
    while(is >> word) {
        auto item = m_words.insert(make_pair(word, nullptr));
        if (item.second) {
            //newly inserted, should init a set here
            item.first->second.reset(new std::set<std::string::size_type>());
            //decltype(*item.first->second);
        }
        item.first->second->insert(line_nr);
    }

    return 0;
}

int MyGrep::do_readin(std::istream &is)
{
    string line;
    while(getline(is, line)) {
        addline(line);
    }

    return 0;
}

std::ostream & MyGrep::print_raw(std::ostream &os)
{
    for(auto &it : *m_lines) {
        cout << it << endl;
    }
    return os;
}

std::ostream & MyGrep::print_words(std::ostream &os)
{
    for(auto &it : m_words) {
        cout << it.first << " --- ";
        for (auto &idx : *it.second) {
            cout << idx << ",";
        }
        cout << endl;
    }
    return os;
}

std::ostream &MyGrep::print_word_info(std::ostream &os, const std::string word)
{
    auto info = m_words.find(word);
    if (info == m_words.end()) {
        cout << "can't find " << word << endl;
    } else {
        cout << "lines containing " << word << " is ==================>" << endl;
        for (auto &idx : *info->second) {
            cout << idx << ": ";
            cout << (*m_lines)[idx] << endl;
        }
    }
}


int mygrep_test(void)
{
    MyGrep grep;

    grep.readin("sales_data2.txt");
    //grep.print_raw(cout);
    //grep.print_words(cout);
    string word;
    cout << "input a word:" << endl;
    while (cin >> word) {
        grep.print_word_info(cout, word);
        cout << endl << endl << endl;
        cout << "input a word:" << endl;
    }
    return 0;
}

