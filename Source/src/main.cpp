#include <iostream>
#include "narrator.hpp"
#include "project.hpp"

int main()
{
    // start by getting globals
    project::Global g = project::Global(1);

    text::Narrator narrator = text::Narrator(&g);
    narrator.print_book();
    std::getchar();
}