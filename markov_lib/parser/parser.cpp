#include "parser.h"

#include <algorithm>
#include <cstring>

#include "../utils/file.h"


void skip_spaces_and_lines(char **ch)
{
    while (**ch == ' ' || **ch == '\n')
    {
        (*ch)++;
    }
}

void skip_spaces(char **ch)
{
    while (**ch == ' ')
    {
        (*ch)++;
    }
}

char parse_symbol(char **ch)
{
    skip_spaces(ch);
   
    char c = **ch;
    skip_spaces(ch);
    if(*(++(*ch)) == ',')
        (*ch)++;

    return c;
}

int parse_array(char **ch, char * mas)
{
    while(**ch != '}' && **ch != '\0')
    {
        skip_spaces(ch);
        char c = parse_symbol(ch);
    
        *mas = c;
        mas++;
    }

    *mas = '\0';
    std::sort(mas, mas+strlen(mas));
    if(**ch != '\0')
    {
        (*ch)++;
        return 0;
    }
    
    return 1;
}

int skip_to_symbol(char **ch, char symbol)
{
    while (**ch != symbol && **ch != '\0')
    {
        (*ch)++;
    }

    if(**ch == symbol)
        return 0;
    return 1;
}

int parse_alphabet(char **ch, char * alp)
{
    skip_to_symbol(ch, '{');
    (*ch)++;
    return parse_array(ch, alp);
}

int parse_command(char **ch,  std::vector<Command> &V, int n)
{
    std::string s1 = "", s2 = "";
    bool is_end = false;
    skip_spaces(ch);
  
    while(isprint(**ch))
    {   
        //cout << **ch << endl;
        if(**ch == ' ')
        {
            if((*((*ch) + 1)) == '-' && (*((*ch) + 2)) == '>')
            {
                *ch += 3;
                if(**ch == '.')
                {(*ch)++ ; is_end = true;}
                break;
            }
        }

        if(**ch == '-' && (*((*ch) + 1)) == '>')
        {
            *ch += 2;
            if(**ch == '.')
            {(*ch)++ ; is_end = true;}
            break;
        }
        s1 += **ch;
        (*ch)++;
    }

    //cout << **ch << endl;
    skip_spaces(ch);
    while (isprint(**ch))
    {
        s2 += **ch;
        (*ch)++;
    }

    Command cm(s1, s2, n, is_end);
    V.push_back(cm);
    skip_spaces_and_lines(ch);

    return **ch == '\0';
}

int parse_commands(char **ch, char *alphabet, char *tuple, std::vector<Command> &V)
{
/*
T = {} // Tuple to work with
A = {} //Alphabet to input

...
//commands
...

*/
    skip_spaces_and_lines(ch);

    for(int i = 0; i < 2; i++)
    {
        skip_spaces_and_lines(ch);
        if(**ch == 'T')
            parse_alphabet(ch, tuple);
        else if(**ch == 'A')
            parse_alphabet(ch, alphabet);
    }

    skip_spaces_and_lines(ch);
    int n = 0;
    while(!parse_command(ch, V, n))
    {
        n++;
    }

    return n;
}