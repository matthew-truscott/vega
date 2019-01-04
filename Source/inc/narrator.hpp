#pragma once

#include <string>

#include "book.hpp"

namespace text {

class Narrator 
{
    bool check_input;
    Book book;
    
  public:
    Narrator();
    ~Narrator();

    void print_book();
};

} // namespace text