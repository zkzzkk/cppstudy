#ifndef _MYGREP_H_
#define _MYGREP_H_
#include <iostream>
#include <string>
#include <fstream>
#include <memory>
#include <vector>
#include <map>
#include <set>

class MyGrep
{
public:
    MyGrep();
   //MyGrep(std::string &file);
   //MyGrep(std::istream &is);
    virtual ~MyGrep();

    int addline(const std::string &line);
    int readin(const std::string &file)
    {
        std::ifstream ifs(file);
        return do_readin(ifs);
    }
    void reset()
    {
        m_lines = nullptr;
        m_words.clear();
    }

    std::ostream &print_raw(std::ostream &os);
    std::ostream &print_words(std::ostream &os);
    std::ostream &print_word_info(std::ostream &os, const std::string word);


protected:

private:
    std::shared_ptr<std::vector<std::string> > m_lines;
    std::map<std::string, std::shared_ptr<std::set<std::string::size_type> > > m_words;

    int do_readin(std::istream &is);
};

int mygrep_test(void);


#endif // _MYGREP_H_
