#pragma once

#include <vector>

#include "../core/MarkovList.h"

struct AlgoConfig {
    std::string rules_fp;
    std::string input_fp;
    std::string output_fp;
};

void RunAlgoritm(MarkovList, const std::vector<Command>&, bool, bool, bool);

const int MAX = 10000;