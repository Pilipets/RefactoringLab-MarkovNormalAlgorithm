#pragma once

#include <vector>
#include <memory>
#include <string>
#include <optional>

#include "../core/MarkovAlgorithm.h"
#include "../core/ListMarkovAlgorithm.h"
#include "../parser/MarkovParser.h"
#include "../utils/FileUtils.h"

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
    std::optional<SimulatorConfig> config;
    AlgorithmStrategy strategy;
    std::unique_ptr<MarkovAlgorithm> algo;

    std::unique_ptr<MarkovAlgorithm> getAlgorithm();
    std::string _getOutput(
        std::string input, bool show_all = false,
        bool simple_db = false, bool full_db = false);

    void _setStrategy(AlgorithmStrategy strategy, std::string alphabet,
        std::string tuple, std::vector<MarkovCommand> commands);

public:
    MarkovAlgoSimulator& setConfig(SimulatorConfig config);

    MarkovAlgoSimulator& setStrategy(
        AlgorithmStrategy strategy, std::string alphabet,
        std::string tuple, std::vector<MarkovCommand> commands);

    MarkovAlgoSimulator& setStrategy(AlgorithmStrategy strategy);

    std::string getOutput();
    std::string getOutput(std::string input);

    void writeOutput();
    void writeOutput(std::string input);
};