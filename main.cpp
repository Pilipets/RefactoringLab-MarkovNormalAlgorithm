#include "markov_lib/MarkovLib.h"

int main()
{
    char Alphabet[100], Tuple[100], *filedata, *input_data;

    auto config = AlgoConfig{"data/alg.txt", "data/inp.txt", "data/out.txt"};

    filedata = read_file(config.rules_fp.c_str());
    input_data = read_file(config.input_fp.c_str());
    char **ch = &filedata;
    
    std::vector<Command> commands;
    parse_commands(&filedata, Alphabet, Tuple, commands);

    MarkovList ML(input_data);
    ML.show();

    RunAlgoritm(ML, commands, true, false, false);
    if (!config.output_fp.empty())
        write_to_file(ML.data_char(), config.output_fp.c_str());

   return 0;
}