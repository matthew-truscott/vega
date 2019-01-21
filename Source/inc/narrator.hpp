#pragma once

#include <string>

#include "book.hpp"
#include "project.hpp"
#include "commander.hpp"
#include "fun.hpp"
#include "actor.hpp"

namespace text {

class Narrator 
{
    bool mCheckInput;
    Book* mBook = nullptr;
    Commander* mCommander = nullptr;
    utils::Fun* mFun = nullptr;
    entity::Actor* mProtagonist = nullptr;
    project::Global* mG;
    int mPageNumber;
    std::string mFunctionInput;
    std::vector<std::string> mParamInput;
    
  public:
    Narrator(project::Global* g);
    ~Narrator();

    void print_book();
    void load();
    int next();
    void process(std::string command);
};

} // namespace text