#include "book.hpp"
#include <iostream>

using namespace text;

Book::Book()
{
    std::cout << "Book Constructor\n";
}

Book::~Book()
{
    std::cout << "Book Destructor\n";
}

void Book::read_page(int page_number)
{
    std::cout << "Hello world!\n";
}