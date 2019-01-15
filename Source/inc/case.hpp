#pragma once

#include <vector>
#include <map>
#include <string>

#include "state.hpp"

namespace utils {

struct Route
{
    Route() : sNext(-1), sMessage("") {}
    int sNext;
    std::string sMessage;
};

class Case 
{
    std::vector<State*> mVecState;
    std::map<std::vector<int>, Route> mCondMap;
    
  public:
    Case(std::vector<State*> vecstate, std::string condstr);
    ~Case();
};

} // namespace text
