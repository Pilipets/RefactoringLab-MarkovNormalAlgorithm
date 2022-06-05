#include "markov_lib/MarkovAlgo.h"


struct AlgoConfig {
    std::string rules_fp;
    std::string input_fp;
    std::string output_fp;
};


int main()
{
    char Alphabet[100], Tuple[100], *filedata, *input_data;

    auto config = AlgoConfig{"data/alg.txt", "data/inp.txt", "data/out.txt"};

    filedata = ReadFileToOne(config.rules_fp.c_str());
    input_data = ReadFileToOne(config.input_fp.c_str());
    char **ch = &filedata;
    
    std::vector<Command> commands;
    extract(&filedata, Alphabet, Tuple, commands);

    MarkovList ML(input_data);
    ML.show();

    RunAlgoritm(ML, commands, true, false, false);
    if (!config.output_fp.empty())
        WriteToFile(ML.data_char(), config.output_fp.c_str());

   return 0;
}