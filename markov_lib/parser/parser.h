#pragma once

#include <vector>
#include "../core/MarkovList.h"


void clear_spaces_and_lines(char **ch);
bool is_command(char *str);
void clear_spaces(char **ch);
bool is_operator(char *str);
bool is_symbol(char *str, char target);
char extract_symbol(char **ch);
int extract_mas(char **ch, char * mas);
int move_to(char **ch, char symbol);
int extract_tuple(char **ch, char *tuple);
int extract_alphabet(char **ch, char * alp);
int one_command(char **ch,  std::vector<Command> &V, int n);
int extract(char **ch, char *alphabet, char *tuple, std::vector<Command> &V);