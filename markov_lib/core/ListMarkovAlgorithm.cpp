#include <iterator>
#ifdef _VERBOSE
#include <cassert>
#include <iostream>
#include <unordered_set>
#endif

#include "ListMarkovAlgorithm.h"

namespace markov_lib::details
{
    ListMarkovAlgorithm::MarkovPtr ListMarkovAlgorithm::_findStr(MarkovPtr ptr,
        const std::string& what)
    {
        // Here ptr is beginning
        int sz = what.size();
        while (ptr != list.end()) {
            if (_isSubstr(ptr, what, 0))
                return ptr;
            ptr++;
        }

        return list.end();
    }

    bool ListMarkovAlgorithm::_isSubstr(MarkovPtr cur, const std::string& s, int pos)
    {
        while (cur != list.end() && pos != s.size() && *cur == s[pos])
            ++cur, ++pos;

        return pos == s.size();
    }

    void ListMarkovAlgorithm::_deleteRange(MarkovPtr beg, int sz)
    {
        // Deletes part starting from beg (beg not included)
        list.erase(std::next(beg), std::next(beg, sz + 1));
    }

    void ListMarkovAlgorithm::_extendRange(MarkovPtr beg, int sz)
    {
        if (sz <= 0)
            return;

        std::list<char> to_insert(sz);
        list.insert(std::next(beg), to_insert.begin(), to_insert.end());
    }

    void ListMarkovAlgorithm::_replaceRange(MarkovPtr ptr, const std::string& s, int i = 0)
    {
        while (i != s.size())
            *ptr++ = s[i++];
    }

    void ListMarkovAlgorithm::_replaceOneStr(MarkovPtr ptr, const std::string& what,
        const std::string& to)
    {
        int diff = what.size() - to.size();
        if (diff > 0) {
            MarkovPtr end = std::next(ptr, to.size() - 1);
            _deleteRange(end, diff);
        }
        else {
            MarkovPtr end = std::next(ptr, what.size() - 1);
            _extendRange(end, abs(diff));
        }
        _replaceRange(ptr, to);
    }

    int ListMarkovAlgorithm::_replaceAllStr(const std::string& from, const std::string& to)
    {
        int i = 0;
        MarkovPtr ptr = list.begin();
        while ((ptr = _findStr(ptr, from)) != list.end()) {
            ++i;
            _replaceOneStr(ptr, from, to);
        }

        return i;
    }

    ListMarkovAlgorithm::ListMarkovAlgorithm(std::string alphabet, std::string tuple, std::vector<MarkovCommand> commands)
        : MarkovAlgorithm(std::move(alphabet), std::move(tuple), std::move(commands))
    {
    }

    std::string ListMarkovAlgorithm::execute(const std::string& input)
    {
        list = std::list<char>(input.begin(), input.end());
#ifdef _VERBOSE
        std::string prev = data();
        std::unordered_set<std::string> data_set;
#endif
        for (const auto& com : commands) {
#ifdef _VERBOSE
            std::cout << prev << "-->";
#endif
            int ret = _replaceAllStr(com.first, com.second);
#ifdef _VERBOSE
            std::string cur = data();
            assert(cur != prev);
            prev = cur;

            std::cout << cur << "\n";
            assert(data_set.insert(std::move(cur)).second);
#endif
            if (ret && com.is_end)
                break;
        }

        return data();
    }

    std::string ListMarkovAlgorithm::data() const
    {
        return std::string(list.begin(), list.end());
    }
}