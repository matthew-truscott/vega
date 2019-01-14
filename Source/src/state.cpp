#include "state.hpp"
#include <iostream>

using namespace utils;

State::State(std::string label, std::vector<std::string> states)
{
    mLabel = label;
    mVecStates = states;
    mStateIdx = 0;
}

State::~State() {}

void State::change_state()
{
    return;
}

std::string State::getname()
{
    return mLabel;
}

std::string State::read_state()
{
    return mVecStates[mStateIdx];
}

std::string State::list_states()
{
    std::string ostr = "";
    for (std::vector<std::string>::const_iterator i = mVecStates.begin();
         i != mVecStates.end();
         ++i)
    {
        ostr += (*i + " ");
    }
    ostr.pop_back();
    return ostr;
}