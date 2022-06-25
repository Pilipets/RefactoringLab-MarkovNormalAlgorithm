#pragma once

#include <string>
#include <vector>

namespace markov_lib
{
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

        virtual std::string execute(const std::string& input) = 0;
        virtual std::string data() const = 0;
    };
}