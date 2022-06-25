#include "parser.h"

#include <algorithm>

namespace markov_lib::parser
{
    void skip_spaces_and_lines(const char** ch)
    {
        while (**ch == ' ' || **ch == '\n') {
            (*ch)++;
        }
    }

    void skip_spaces(const char** ch)
    {
        while (**ch == ' ') {
            (*ch)++;
        }
    }

    char parse_symbol(const char** ch)
    {
        skip_spaces(ch);

        char c = **ch;
        skip_spaces(ch);
        if (*(++(*ch)) == ',')
            (*ch)++;

        return c;
    }

    int parse_array(const char** ch, std::string& arr)
    {
        while (**ch != '}' && **ch != '\0') {
            skip_spaces(ch);
            char c = parse_symbol(ch);

            arr.push_back(c);
        }

        arr.push_back('\0');
        std::sort(arr.begin(), arr.end());
        if (**ch != '\0') {
            (*ch)++;
            return 0;
        }

        return 1;
    }

    int skip_to_symbol(const char** ch, char symbol)
    {
        while (**ch != symbol && **ch != '\0') {
            (*ch)++;
        }

        if (**ch == symbol)
            return 0;
        return 1;
    }

    int parse_alphabet(const char** ch, std::string& alphabet)
    {
        skip_to_symbol(ch, '{');
        (*ch)++;
        return parse_array(ch, alphabet);
    }

    int parse_command(const char** ch, std::vector<markov_lib::MarkovCommand>& commands, int n)
    {
        std::string s1 = "", s2 = "";
        bool is_end = false;
        skip_spaces(ch);

        while (isprint(**ch)) {
            if (**ch == ' ') {
                if ((*((*ch) + 1)) == '-' && (*((*ch) + 2)) == '>') {
                    *ch += 3;
                    if (**ch == '.') {
                        (*ch)++;
                        is_end = true;
                    }
                    break;
                }
            }

            if (**ch == '-' && (*((*ch) + 1)) == '>') {
                *ch += 2;
                if (**ch == '.') {
                    (*ch)++;
                    is_end = true;
                }
                break;
            }
            s1 += **ch;
            (*ch)++;
        }

        skip_spaces(ch);
        while (isprint(**ch)) {
            s2 += **ch;
            (*ch)++;
        }

        commands.emplace_back(std::move(s1), std::move(s2), n, is_end);
        skip_spaces_and_lines(ch);

        return **ch == '\0';
    }

    int parse_commands(
        const char* input,
        std::string& alphabet,
        std::string& tuple,
        std::vector<markov_lib::MarkovCommand>& commands)
    {

        const char** ch = &input;
        skip_spaces_and_lines(ch);

        for (int i = 0; i < 2; i++) {
            skip_spaces_and_lines(ch);
            if (**ch == 'T')
                parse_alphabet(ch, tuple);
            else if (**ch == 'A')
                parse_alphabet(ch, alphabet);
        }

        skip_spaces_and_lines(ch);
        int n = 0;
        while (!parse_command(ch, commands, n)) {
            n++;
        }

        return n;
    }
}