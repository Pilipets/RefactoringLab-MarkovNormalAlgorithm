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
    using MarkovPtr = decltype(list.begin());

    //functions
    MarkovPtr Search(MarkovPtr ptr, const std::string& what);
    bool IsIt(MarkovPtr cur, const std::string& s, int pos);
    MarkovPtr MoveTo(MarkovPtr cur, int sz);

    //operations 
    void CreateNewParts(int);
    void DeleteParts(MarkovPtr beg, int sz);
    void ReplaceValue(MarkovPtr ptr, const std::string& s, int i);
    void AddParts(MarkovPtr beg, int sz);
    void Replace(MarkovPtr ptr, const std::string& what, const std::string& to);

public:
    MarkovList(char* s);
    MarkovList(const std::string& s);

    int size();
    int replace(const std::string& what, const std::string& to);
    void show();
    std::string data();
    char * data_char();
};