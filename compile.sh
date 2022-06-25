#!/bin/bash
g++ main.cpp markov_lib/core/*.cpp markov_lib/parser/*.cpp markov_lib/simulator/*.cpp markov_lib/utils/*.cpp -o main --std=c++20 -D_VERBOSE