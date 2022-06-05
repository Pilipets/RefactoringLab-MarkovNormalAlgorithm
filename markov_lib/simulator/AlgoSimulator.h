#pragma once

#include <vector>

#include "../core/MarkovList.h"

struct AlgoConfig {
    std::string rules_fp;
    std::string input_fp;
    std::string output_fp;
};

void RunAlgoritm(
    MarkovList ML,
    const std::vector<Command>& commands,
    bool show_all, bool simple_db, bool full_db);

const int MAX = 10000;