#pragma once

#include <vector>
#include <memory>
#include <string>

#include "../core/MarkovAlgorithm.h"
#include "../core/ListMarkovAlgorithm.h"
#include "../parser/parser.h"
#include "../utils/file_utils.h"

namespace markov_lib
{
    struct SimulatorConfig {
        std::string rules_fp;
        std::string input_fp;
        std::string output_fp;
    };

    class MarkovAlgoSimulator {
    public:
        enum AlgorithmStrategy {
            NONE,
            LIST_MARKOV_ALGO
        };

    private:
        SimulatorConfig config;
        AlgorithmStrategy strategy;
        std::unique_ptr<MarkovAlgorithm> algo;

        std::unique_ptr<MarkovAlgorithm> getAlgorithm();
        std::string _getOutput(std::string input);

        void _setStrategy(AlgorithmStrategy strategy, std::string alphabet,
            std::string tuple, std::vector<MarkovCommand> commands);

    public:
        MarkovAlgoSimulator& setConfig(SimulatorConfig config);

        MarkovAlgoSimulator& setStrategy(
            AlgorithmStrategy strategy, std::string alphabet,
            std::string tuple, std::vector<MarkovCommand> commands);

        MarkovAlgoSimulator& setStrategy(AlgorithmStrategy strategy);

        std::string getOutput(const std::string& input = {});
        std::string writeOutput(const std::string& input = {});
    };
}