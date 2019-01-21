#include "narrator.hpp"
#include <iostream>

using namespace text;

Narrator::Narrator(project::Global* g)
{
    mG = g;
    if (mG->gVerbose > 0) std::cout << "Narrator Constructor\n";
    mCheckInput = false;
    mFun = new utils::Fun();
    mCommander = new Commander(g);
    mProtagonist = new entity::Actor();
    mBook = new Book(g, mFun, mProtagonist);
    mPageNumber = 0;
}

Narrator::~Narrator()
{
    std::cout << "Narrator Destructor\n";
}

void Narrator::load()
{
    if (mG->gVerbose > 0)
    {
        mCommander->printFunctions();
        mCommander->printParameters();
    }

    mBook->read_page(mPageNumber);
}

int Narrator::next()
{
    if (mProtagonist->IsAlive()) 
    {
        mBook->print_page();
        return 0;
    }
    else
    {
        return -1;
    }
}

void Narrator::print_book()
{
    mBook->read_page(0);
}

void Narrator::process(std::string command)
{
    mFunctionInput = mCommander->getFunction(command);
    mParamInput = mCommander->getParameters(command);

    int iResult = mBook->check_input(mFunctionInput, mParamInput);
}