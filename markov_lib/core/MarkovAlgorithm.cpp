#include "MarkovAlgorithm.h"

namespace markov_lib
{
    MarkovAlgorithm::MarkovAlgorithm(std::string alphabet, std::string tuple, std::vector<MarkovCommand> commands)
        : alphabet(std::move(alphabet))
        , tuple(std::move(tuple))
        , commands(std::move(commands))
    {
    }
}