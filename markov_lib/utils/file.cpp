#include "file.h"


bool read_line(FILE *file, char * ret)
{
    char c;
    bool res = false;
    
    while ((c = fgetc(file)) != EOF && c != '\n')
    {

        *ret = c;
        ret++;
        res = true;
        

    }
    if (c == '\n')
        res = true;
    
    *ret = '\0';

    return  res;
}

std::vector<char *> read_lines(char *filename)
{
    FILE *file;
    std::vector<char *> ret;
    file = fopen(filename, "r");
    if(file == NULL)
    {    printf("Error while opening file \n"); return ret;}
    
    char *line = new char[128];
    size_t len;
    ssize_t read;
    
    while (read_line(file, line))
    {
        ret.push_back(line);
        line = new char[128];
    }

    return ret;
}

char* read_file(const char *filename)
{
    FILE *file;
    char *ret = NULL, *cp, c;
    file = fopen(filename, "r");
    if(file == NULL)
    {
        printf("Error while opening file \n");
        return ret;
    }

    ret = new char[100000];
    cp = ret;

    while ((c = fgetc(file)) != EOF)
    {
        *cp = c;
        cp++;
    }
    *cp = '\n';

    return ret;
}

void write_to_file(char* data, const char* filename)
{
    FILE *file; 

    file = fopen(filename, "w");
    fputs(data, file);
}
