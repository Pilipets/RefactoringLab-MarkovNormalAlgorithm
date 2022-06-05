#include "MarkovList.h"

#include <iostream>
#include <cstring>
#include <cassert>
#include <iterator>

Command::Command(std::string s1, std::string s2, int num,  bool c_end)
{
    first = std::move(s1);
    second = std::move(s2);
    is_end = c_end;
    n = num;
}

void MarkovList::CreateNewParts(int add_size)
{
    if (add_size <= 0)
        return;

    list.resize(add_size);
}

MarkovList::MarkovList(char* s)
{
    CreateNewParts(std::strlen(s));
    MarkovPtr ptr = list.begin();

    while(std::next(ptr) != list.end())
    {
        *ptr++ = *s++;
    }
}

MarkovList::MarkovList(const std::string& s)
{
    int sz = s.size();
    CreateNewParts(sz);
    MarkovPtr ptr = list.begin();

    for(int i = 0; i < sz; ++i)
    {
        *ptr = s[i];
        ptr++;
    }
}   

bool MarkovList::IsIt(MarkovPtr cur, const std::string& s, int pos)
{
    while (cur != list.end() && pos != s.size() && *cur == s[pos])
        ++cur, ++pos;

    return pos == s.size();
}

MarkovList::MarkovPtr MarkovList::Search(MarkovPtr ptr, const std::string& what)
{
    //Here ptr is begigning

    int sz = what.size();
    while (ptr != list.end())
    {
        if(IsIt(ptr, what, 0))
            return ptr;
        ptr++;
    }

    return list.end();
    
}

MarkovList::MarkovPtr MarkovList::MoveTo(MarkovPtr cur, int sz)
{
    return std::next(cur, sz);
}

void MarkovList::AddParts(MarkovPtr beg, int sz)
{
    if (sz <= 0)
        return;

    std::list<char> to_insert(sz);
    list.insert(std::next(beg), to_insert.begin(), to_insert.end());
}

void MarkovList::DeleteParts(MarkovPtr beg, int sz)
{
    //Deltes part starting from beg (beg not included)
    list.erase(std::next(beg), std::next(beg, sz+1));
}

void MarkovList::ReplaceValue(MarkovPtr ptr, const std::string& s, int i = 0)
{
    if(s.size() == i)
        return;

    assert(ptr != list.end());

    *ptr = s[i];
    ReplaceValue(++ptr, s, i+1);
}

void MarkovList::Replace(MarkovPtr ptr, const std::string& what, const std::string& to)
{
    int diff = what.size() - to.size();
    if(diff > 0)
    {
        MarkovPtr end = MoveTo(ptr, to.size()-1);
        DeleteParts(end, diff);
    }
    else
    {
        MarkovPtr end = MoveTo(ptr, what.size()-1);
        AddParts(end, abs(diff));

    }
    ReplaceValue(ptr, to);
}

void MarkovList::show()
{
    for (char ch : list)
        std::cout << ch;
    std::cout << '\n';
}

std::string MarkovList::data()
{
    return std::string(list.begin(), list.end());
}

int MarkovList::replace(const std::string& what, const std::string& to)
{
    int i = 0;
    MarkovPtr ptr = list.begin();
    while((ptr = Search(ptr, what)) != list.end())
    {
        ++i;
        Replace(ptr, what, to);
    }

    return i;
}

char* MarkovList::data_char()
{
    char* out = new char[list.size()];

    MarkovPtr ptr = list.begin();
    for (size_t i = 0; i < list.size(); ++i)
        out[i] = *ptr++;

    return out;
}