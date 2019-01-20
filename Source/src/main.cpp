#include <iostream>
#include "narrator.hpp"
#include "commander.hpp"
#include "project.hpp"

int main()
{
    // start by getting globals
    project::Global g = project::Global(1);

    text::Narrator narrator = text::Narrator(&g);
    text::Commander commander = text::Commander(&g);

    narrator.load();

    std::string commandInput; 
    std::string functionInput;
    std::vector<std::string> paramInput;

    if (g.gVerbose > 0)
    {
        commander.printFunctions();
        commander.printParameters();
    }
    
    while (commandInput != "q")
    {
        commandInput.clear();

        narrator.next();

        getline(std::cin, commandInput);        

        functionInput = commander.getFunction(commandInput);

        paramInput = commander.getParameters(commandInput);
    }
}