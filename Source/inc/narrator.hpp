#pragma once

#include <string>

#include "book.hpp"
#include "project.hpp"

namespace text {

class Narrator 
{
    bool mCheckInput;
    Book* mBook = nullptr;
    project::Global* mG;
    
  public:
    Narrator(project::Global* g);
    ~Narrator();

    void print_book();
};

} // namespace text