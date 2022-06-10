#include "MarkovAlgorithm.h"

MarkovAlgorithm::MarkovAlgorithm(std::string alphabet, std::string tuple, std::vector<MarkovCommand> commands):
    alphabet(std::move(alphabet)), tuple(std::move(tuple)), commands(std::move(commands))
{}
