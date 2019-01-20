#include <iostream>

#include "case.hpp"

using namespace utils;

Case::Case(project::Global* g, 
           std::vector<State*> vecstate, 
           std::map<std::string, std::string>* condmap)
{

    mVecState = vecstate;
    mG = g;

    if (mG->gVerbose > 0) std::cout << "Case Constructor\n";

    for (std::map<std::string, std::string>::iterator iter = condmap->begin();
         iter != condmap->end();
         ++iter)
    {
        std::string condstr = iter->first;
        std::string routestr = iter->second;

        // parse the key
        std::vector<int> tVecKey;

        size_t next = condstr.find(mG->case_delimiter_cond);
        if (next != std::string::npos) 
        {
            condstr.erase(0, next + mG->case_delimiter_cond.length());
        }

        std::string tKey;
        while (next = condstr.find(mG->case_delimiter_cond) != std::string::npos)
        {
            tKey = condstr.substr(0, next);
            if (tKey == "A")
            {
                // any key, replace with -1
                tVecKey.push_back(-1);
            }
            else tVecKey.push_back(std::stoi(tKey, nullptr));

            condstr.erase(0, next + mG->case_delimiter_cond.length());
        }

        tKey = condstr;
        tVecKey.push_back(std::stoi(tKey, nullptr));

        if (mG->gVerbose > 0)
        {
            std::cout << "Vector contents: ";
            for (std::vector<int>::iterator j = tVecKey.begin();
                j != tVecKey.end();
                ++j)
            {
                std::cout << *j << " ";
            }
            std::cout << "\n";
        }

        // parse the route
        size_t tPosOpen = routestr.find(mG->case_goto_open);
        size_t tPosClose = routestr.find(mG->case_goto_close);
        size_t tLenOpen = mG->case_goto_open.length();
        size_t tLenClose = mG->case_goto_close.length();

        int tNext = std::stoi(routestr.substr(tPosOpen+tLenOpen, 
            tPosClose-1), nullptr);
        std::string tMessage = routestr.substr(tPosClose+tLenClose);

        if (mG->gVerbose > 0)
        {
            std::cout << "\tNext: " << tNext << "\n";
            std::cout << "\tMessage: " << tMessage << "\n";
        }
    }
}

    