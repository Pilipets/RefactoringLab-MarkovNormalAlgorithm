#include <vector>
#include <stdio.h>

bool read_line(FILE *file, char * ret);
char* read_file(const char *filename);
std::vector<char *> read_lines(char *filename);
void write_to_file(char* data, const char* filename);