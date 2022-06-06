#include <cassert>
#include <cstring>
#include <iostream>
#include <iterator>

#include "MarkovList.h"

MarkovList::MarkovList(char* s) : list(s, s + std::strlen(s)) {}

MarkovList::MarkovList(const std::string& s) : list(s.begin(), s.end()) {}

bool MarkovList::_isSubstr(MarkovPtr cur, const std::string& s, int pos) {
    while (cur != list.end() && pos != s.size() && *cur == s[pos]) ++cur, ++pos;

    return pos == s.size();
}

MarkovList::MarkovPtr MarkovList::_findStr(MarkovPtr ptr,
                                           const std::string& what) {
    // Here ptr is beginning

    int sz = what.size();
    while (ptr != list.end()) {
        if (_isSubstr(ptr, what, 0)) return ptr;
        ptr++;
    }

    return list.end();
}

void MarkovList::_extendRange(MarkovPtr beg, int sz) {
    if (sz <= 0) return;

    std::list<char> to_insert(sz);
    list.insert(std::next(beg), to_insert.begin(), to_insert.end());
}

void MarkovList::_deleteRange(MarkovPtr beg, int sz) {
    // Deletes part starting from beg (beg not included)
    list.erase(std::next(beg), std::next(beg, sz + 1));
}

void MarkovList::_replaceRange(MarkovPtr ptr, const std::string& s, int i = 0) {
    while (i != s.size()) *ptr++ = s[i++];
}

void MarkovList::_replaceStr(MarkovPtr ptr, const std::string& what,
                             const std::string& to) {
    int diff = what.size() - to.size();
    if (diff > 0) {
        MarkovPtr end = std::next(ptr, to.size() - 1);
        _deleteRange(end, diff);
    } else {
        MarkovPtr end = std::next(ptr, what.size() - 1);
        _extendRange(end, abs(diff));
    }
    _replaceRange(ptr, to);
}

void MarkovList::show() {
    for (char ch : list) std::cout << ch;
    std::cout << '\n';
}

std::string MarkovList::data() { return std::string(list.begin(), list.end()); }

int MarkovList::replace(const std::string& what, const std::string& to) {
    int i = 0;
    MarkovPtr ptr = list.begin();
    while ((ptr = _findStr(ptr, what)) != list.end()) {
        ++i;
        _replaceStr(ptr, what, to);
    }

    return i;
}

char* MarkovList::data_char() {
    char* out = new char[list.size() + 1];

    MarkovPtr ptr = list.begin();
    for (size_t i = 0; i < list.size(); ++i) out[i] = *ptr++;

    out[list.size()] = '\0';
    return out;
}