#pragma once

#include <string>
#include <vector>

namespace utils {

class State 
{
    std::string mLabel;
    std::vector<std::string> mVecStates;
    int mStateIdx;
    
  public:
    State(std::string label, std::vector<std::string> states);
    ~State();

    void change_state();
    std::string getname();
    std::string read_state();
    std::string list_states();
};

} // namespace text