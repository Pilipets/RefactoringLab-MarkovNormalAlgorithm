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

                auto file_data = read_file(config.rules_fp.data());
                parse_commands(file_data.data(), alphabet, tuple, commands);
            }

            _setStrategy(strategy, std::move(alphabet), std::move(tuple), std::move(commands));
        }

        return *this;
    }

    std::string MarkovAlgoSimulator::getOutput(const std::string& input)
    {
        // Take arg or read from config
        if (input.size()) {
            return _getOutput(input);
        }
        else {
            auto input_str = read_file(config.input_fp.data());
            return _getOutput(input_str);
        }
    }

    std::string MarkovAlgoSimulator::writeOutput(const std::string& input)
    {
        auto output = getOutput(input);
        write_to_file(output.data(), config.output_fp.data());
        return output;
    }
}