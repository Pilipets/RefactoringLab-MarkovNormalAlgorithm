#pragma once

#include <vector>

#include "../core/MarkovAlgorithm.h"

namespace markov_lib::parser
{
    void skip_spaces_and_lines(const char** ch);
    void skip_spaces(const char** ch);
    char parse_symbol(const char** ch);
    int parse_array(const char** ch, std::string& arr);
    int skip_to_symbol(const char** ch, char symbol);
    int parse_alphabet(const char** ch, std::string& alphabet);
    int parse_command(const char** ch, std::vector<markov_lib::MarkovCommand>& commands, int n);
    int parse_commands(
        const char* input,
        std::string& alphabet,
        std::string& tuple,
        std::vector<markov_lib::MarkovCommand>& commands);
}