#pragma once

#include "MarkovAlgorithm.h"

#include <list>

class ListMarkovAlgorithm : public MarkovAlgorithm {
    std::list<char> list;
    using MarkovPtr = decltype(list)::iterator;

    // helper functions
    MarkovPtr _findStr(MarkovPtr ptr, const std::string& what);
    bool _isSubstr(MarkovPtr cur, const std::string& s, int pos);

    // sub-main operations
    void _deleteRange(MarkovPtr beg, int sz);
    void _replaceRange(MarkovPtr ptr, const std::string& s, int i);
    void _extendRange(MarkovPtr beg, int sz);
    void _replaceOneStr(MarkovPtr ptr, const std::string& from, const std::string& to);

    // main operations
    int _replaceAllStr(const std::string& from, const std::string& to);

public:
    ListMarkovAlgorithm(std::string alphabet, std::string tuple, std::vector<MarkovCommand> commands);

    std::string execute(std::string input) override;
    std::string data() const override;

    /*void initSteps(std::string input) override;
    std::string executeStep() override;*/
};