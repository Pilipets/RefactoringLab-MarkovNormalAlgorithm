#include <iostream>
#include <unordered_set>

#include "MarkovAlgoSimulator.h"

namespace markov_lib
{
    using namespace utils;
    using namespace details;
    using namespace parser;

    std::string MarkovAlgoSimulator::_getOutput(std::string input)
    {

        return algo->execute(std::move(input));
    }

    void MarkovAlgoSimulator::_setStrategy(
        AlgorithmStrategy strategy, std::string alphabet,
        std::string tuple, std::vector<MarkovCommand> commands)
    {

        if (strategy == AlgorithmStrategy::LIST_MARKOV_ALGO) {
            algo = std::make_unique<ListMarkovAlgorithm>(
                std::move(alphabet),
                std::move(tuple),
                std::move(commands));
        }
        else {
            algo = nullptr;
        }

        this->strategy = strategy;
    }

    MarkovAlgoSimulator& MarkovAlgoSimulator::setConfig(SimulatorConfig config)
    {
        this->config = std::move(config);
        return *this;
    }

    MarkovAlgoSimulator& MarkovAlgoSimulator::setStrategy(
        AlgorithmStrategy strategy, std::string alphabet,
        std::string tuple, std::vector<MarkovCommand> commands)
    {

        if (this->strategy != strategy) {
            _setStrategy(strategy, std::move(alphabet), std::move(tuple), std::move(commands));
        }

        return *this;
    }

    MarkovAlgoSimulator& MarkovAlgoSimulator::setStrategy(AlgorithmStrategy strategy)
    {
        if (this->strategy != strategy) {

            std::string alphabet, tuple;
            std::vector<MarkovCommand> commands;

            if (strategy != AlgorithmStrategy::NONE) {

                auto file_data = read_file(config->rules_fp.data());
                parse_commands(file_data.data(), alphabet, tuple, commands);
            }

            _setStrategy(strategy, std::move(alphabet), std::move(tuple), std::move(commands));
        }

        return *this;
    }

    std::string MarkovAlgoSimulator::getOutput()
    {
        std::string input = read_file(config->input_fp.data());
        return _getOutput(std::move(input));
    }

    std::string MarkovAlgoSimulator::getOutput(std::string input)
    {
        return _getOutput(std::move(input));
    }

    void MarkovAlgoSimulator::writeOutput()
    {
        std::string input = read_file(config->input_fp.data());
        auto output = _getOutput(std::move(input));
        write_to_file(output.data(), config->output_fp.data());
    }

    void MarkovAlgoSimulator::writeOutput(std::string input)
    {
        auto output = _getOutput(std::move(input));
        write_to_file(output.data(), config->output_fp.data());
    }
}