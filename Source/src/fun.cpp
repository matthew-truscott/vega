#include "fun.hpp"

#include <utility>
#include <iostream>

using namespace utils;

Fun::Fun()
{
    mMapArgs["search"] = 1;
    mMapArgs["leave"] = 0;
    mMapArgs["attack"] = 1;
    mMapArgs["move"] = 1;
    mMapArgs["sleep"] = 0;
    mMapArgs["status"] = 0;
    mMapArgs["help"] = 0;

    mMapFun["search"] = FunName::SEARCH;
    mMapFun["leave"] = FunName::LEAVE;
    mMapFun["attack"] = FunName::ATTACK;
    mMapFun["move"] = FunName::MOVE;
    mMapFun["sleep"] = FunName::SLEEP;
    mMapFun["status"] = FunName::STATUS;
    mMapFun["help"] = FunName::HELP;
}

Fun::~Fun()
{

}

void Fun::Search()
{
    std::cout << "Search\n";
}

void Fun::Leave()
{
    std::cout << "Leave\n";
}

void Fun::Attack()
{
    std::cout << "Attack\n";
}

void Fun::Move()
{
    std::cout << "Move\n";
}

void Fun::Sleep(Page* page, entity::Actor* player)
{
    std::cout << "Sleep...\n";
    // get relevant state
    for (auto iter = page->sVecState.begin(); iter != page->sVecState.end(); ++iter)
    {
        if ((*iter)->getname().compare("safe") == 0)
        {
            if ((*iter)->read_state().compare("0") == 0)
            {
                std::cout << "You fall into an eternal slumber\n";
                player->Kill();
            }
            else
            {
                std::cout << "The rest is somewhat refreshing\n";
            }
            return;
        }
    }
    
    // assume safe
    std::cout << "The rest is somewhat refreshing\n";
    return;
}

void Fun::Status()
{
    std::cout << "Status\n";
}

void Fun::Help()
{
    std::cout << "Help\n";
}



int Fun::GetNumArg(std::string name)
{
    return mMapArgs[name];
}

void Fun::ExecFunction(std::string name, std::vector<std::string>* params, Page* page,
    entity::Actor* player)
{
    // for now use case statement... (look into closures/functors/lambdas)
    // TODO: Do something nicer here

    switch(mMapFun[name]) 
    {
        case FunName::SEARCH:
            Search();
            break;
        case FunName::LEAVE:
            Leave();
            break;
        case FunName::ATTACK:
            Attack();
            break;
        case FunName::MOVE:
            Move();
            break;
        case FunName::SLEEP:
            Sleep(page, player);
            break;
        case FunName::STATUS:
            Status();
            break;
        case FunName::HELP:
            Help();
            break;
        default:
            break;
    }

    return;
}