#pragma once

#include <string>
#include <nlohmann/json.hpp>

#include "project.hpp"
#include "state.hpp"
#include "case.hpp"
#include "fun.hpp"
#include "page.hpp"
#include "actor.hpp"

using json = nlohmann::json;

namespace text {

class Book 
{
    int mBookLength;
    Page* mPage;
    project::Global* mG;
    utils::Fun* mF;

    std::string mFunc;
    std::vector<std::string> mVecParam;
    entity::Actor* mProtagonist;
    
  public:
    Book(project::Global* g, utils::Fun* f, entity::Actor* p);
    ~Book();

    void read_page(int pageNumber);
    void print_page();
    int check_input(std::string functionInput, std::vector<std::string> paramInput);
};

} // namespace text
