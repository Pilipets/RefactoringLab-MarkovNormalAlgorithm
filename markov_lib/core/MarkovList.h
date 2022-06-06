#pragma once

#include <string>
#include <list>


struct Command
{
    std::string first;
    std::string second;
    bool is_end;
    int n;

    Command(std::string s1, std::string s2, int num,  bool c_end);
};


class MarkovList
{
    std::list<char> list;
    using MarkovPtr = decltype(list)::iterator;

    //functions
    MarkovPtr _findStr(MarkovPtr ptr, const std::string& what);
    bool _isSubstr(MarkovPtr cur, const std::string& s, int pos);

    //operations
    void _deleteRange(MarkovPtr beg, int sz);
    void _replaceRange(MarkovPtr ptr, const std::string& s, int i);
    void _extendRange(MarkovPtr beg, int sz);
    void _replaceStr(MarkovPtr ptr, const std::string& what, const std::string& to);

public:
    MarkovList(char* s);
    MarkovList(const std::string& s);

    int size();
    int replace(const std::string& what, const std::string& to);
    void show();
    std::string data();
    char* data_char();
};