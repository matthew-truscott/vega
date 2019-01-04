#include "narrator.hpp"
#include <iostream>

using namespace text;

Narrator::Narrator()
{
    std::cout << "Narrator Constructor\n";
    check_input = false;
}

Narrator::~Narrator()
{
    std::cout << "Narrator Destructor\n";
}

void Narrator::print_book()
{
    book.read_page(1);
}