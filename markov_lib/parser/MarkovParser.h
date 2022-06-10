#pragma once

#include <vector>

#include "../core/MarkovAlgorithm.h"

void skip_spaces_and_lines(char **ch);
void skip_spaces(char **ch);
char parse_symbol(char **ch);
int parse_array(char **ch, char *mas);
int skip_to_symbol(char **ch, char symbol);
int parse_alphabet(char **ch, char *alp);
int parse_command(char **ch, std::vector<MarkovCommand> &V, int n);
int parse_commands(char **ch, char *alphabet, char *tuple, std::vector<MarkovCommand> &V);