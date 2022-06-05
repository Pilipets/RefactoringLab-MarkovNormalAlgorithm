#include <vector>
#include <stdio.h>

bool readline(FILE *file, char * ret);
char * ReadFileToOne(const char *filename);
std::vector<char *> read_file(char *filename);
void WriteToFile(char* data, const char*);