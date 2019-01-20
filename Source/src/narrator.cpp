#include "narrator.hpp"
#include <iostream>

using namespace text;

Narrator::Narrator(project::Global* g)
{
    mG = g;
    if (mG->gVerbose > 0) std::cout << "Narrator Constructor\n";
    mCheckInput = false;
    mBook = new Book(g);
    mPageNumber = 0;
}

Narrator::~Narrator()
{
    std::cout << "Narrator Destructor\n";
}

void Narrator::load()
{
    mBook->read_page(mPageNumber);
}

void Narrator::next()
{
    mBook->print_page();
}

void Narrator::print_book()
{
    mBook->read_page(0);
}