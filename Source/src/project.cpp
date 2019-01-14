#include <iostream>

#include "project.hpp"

using namespace project;

// TODO: convert to singleton 
// https://stackoverflow.com/questions/1008019/c-singleton-design-pattern

Global::Global(int verbose)
{
    std::cout << "Global Constructor\n";
    json_dir = "dat";
    setting_delimiter_open = "[";
    setting_delimiter_close = "]";
    setting_delimiter_sep = "|";
    gVerbose = verbose;
    std::cout << "Verbosity set to " + std::to_string(gVerbose) + "\n";
}

Global::~Global()
{
    std::cout << "Global Destructor\n";
}