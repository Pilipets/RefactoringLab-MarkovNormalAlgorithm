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
    MarkovPtr GiveLast();
    MarkovPtr Search(MarkovPtr ptr, std::string what);

    bool IsIt(MarkovPtr cur, std::string s, int pos);

    MarkovPtr MoveTo(MarkovPtr, int);

    //operations 
    void CreateNewParts(int);
    void DeleteParts(MarkovPtr beg, int sz);
    void ReplaceValue(MarkovPtr ptr, std::string s, int i);
    void AddParts(MarkovPtr beg, int sz);
    void Replace(MarkovPtr ptr,std::string what, std::string to);

public:
    MarkovList(char* s);
    MarkovList(std::string s);

    int size();
    int replace(std::string what, std::string to);
    void show();
    std::string data();
    char * data_char();

};