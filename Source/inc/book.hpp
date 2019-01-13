#pragma once

#include <string>
#include <nlohmann/json.hpp>

#include "project.hpp"

using json = nlohmann::json;

namespace text {

struct Page
{
    Page() : sPageNumber(-1), sLabel(""), sContent("") {}
    int sPageNumber;
    std::string sLabel;
    std::string sContent;
};

class Book 
{
    int mBookLength;
    Page* mPage;
    project::Global* mG;
    
  public:
    Book(project::Global* g);
    ~Book();

    void read_page(int pageNumber);
    void print_page();
};

} // namespace text
