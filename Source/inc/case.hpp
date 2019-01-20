#pragma once

#include <vector>
#include <map>
#include <string>

#include "state.hpp"
#include "project.hpp"

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
    project::Global* mG;

    /*
     * This object is somewhat difficult to define. We need a mapping between
     * a set of conditionals and the result in such a way that doesn't involve
     * checking every single conditional. We store the conditionals in an int
     * vector that is passed in through a properly formatted string of ints
     * separated by some delimiter @. 
     * 
     */
    std::map<std::vector<int>, Route> mCondMap;
    
  public:
    Case(project::Global* g, std::vector<State*> vecstate, std::map<std::string, std::string>* condmap);
    ~Case();
};

} // namespace text
