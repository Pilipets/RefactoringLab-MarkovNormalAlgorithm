#include "FileUtils.h"

#include <cstring>
#include <streambuf>

bool read_line(std::ifstream& fin, std::string& line) {
    return static_cast<bool>(std::getline(fin, line));
}

std::vector<std::string> read_lines(const char *filename) {
    std::ifstream fin(filename);

    std::vector<std::string> file_lines;
    std::string line;
    while(read_line(fin, line)) {
        file_lines.push_back(std::move(line));
    }

    return file_lines;
}

std::string read_file(const char *filename) {
    std::ifstream fin(filename);
    return std::string(
        std::istreambuf_iterator<char>(fin),
        std::istreambuf_iterator<char>()
    );
}

void write_to_file(const char *data, const char *filename) {
    std::ofstream(filename).write(data, std::strlen(data));
}