#pragma once

#include <string>
#include <vector>

struct MarkovCommand {
    std::string first;
    std::string second;
    int num;
    bool is_end;
};

class MarkovAlgorithm {
protected:
    std::string alphabet, tuple;
    std::vector<MarkovCommand> commands;

public:
    MarkovAlgorithm(std::string alphabet, std::string tuple, std::vector<MarkovCommand> commands);

    virtual std::string execute(std::string input) = 0;
    virtual std::string data() const = 0;

    // Might be present or not
    /*virtual void initSteps(std::string input) {};
    virtual std::string executeStep() {};*/
};