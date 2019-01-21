#pragma once

#include <string>
#include <vector>

#include "case.hpp"
#include "state.hpp"

struct Page
{
    Page() : sPageNumber(-1), sLabel(""), sContent("") {}
    int sPageNumber;
    std::string sLabel;
    std::string sContent;
    std::vector<std::string> sVecParam;
    std::vector<std::string> sVecFunc;
    std::vector<utils::State*> sVecState;
    utils::Case* sCase;
};