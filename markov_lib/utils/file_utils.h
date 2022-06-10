#pragma once

#include <vector>
#include <fstream>

namespace markov_lib::utils
{
    bool read_line(std::istream & in, std::string & ret);
    std::string read_file(const char* filename);
    std::vector<std::string> read_lines(const char* filename);
    void write_to_file(const char* data, const char* filename);
}