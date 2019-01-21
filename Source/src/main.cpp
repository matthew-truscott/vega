#include <iostream>
#include "narrator.hpp"
#include "commander.hpp"
#include "project.hpp"

int main()
{
    // start by getting globals
    project::Global g = project::Global(1);

    text::Narrator narrator = text::Narrator(&g);

    narrator.load();

    std::string commandInput; 
    int status = 0;
    
    while (commandInput != "q")
    {
        commandInput.clear();

        status = narrator.next();

        if (status < 0) break;

        getline(std::cin, commandInput);  

        narrator.process(commandInput);
    }

    std::cout << "GAME OVER\n";
    getline(std::cin, commandInput);
}