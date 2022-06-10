#include "markov_lib/MarkovAlgo.h"

#include <memory>
#include <iostream>

int main()
{
    using namespace markov_lib;
    MarkovAlgoSimulator sim;

    sim
        .setConfig({ "data/alg.txt", "data/inp.txt", "data/out.txt" })
        .setStrategy(MarkovAlgoSimulator::AlgorithmStrategy::LIST_MARKOV_ALGO);

    auto output = sim.getOutput();
    std::cout << "Output: " << output << "\n\n";

    sim.writeOutput();
    std::cout << "\n";

    auto input_data = utils::read_file("data/inp.txt");
    output = sim.getOutput(input_data);
    std::cout << "\n";

    std::cout << "Input: " << input_data << "\n";
    std::cout << "Output: " << output << "\n";

    return 0;
}