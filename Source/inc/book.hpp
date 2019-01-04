#pragma once

#include <string>
#include <nlohmann/json.hpp>

namespace text {

struct Page
{
    int page_number;
    std::string content;
};

class Book 
{
    int book_length;
    Page* page;
    
  public:
    Book();
    ~Book();

    void read_page(int page_number);
};

} // namespace text
