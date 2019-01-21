#pragma once

#include <string>
#include <map>
#include <vector>

#include "page.hpp"
#include "actor.hpp"

namespace utils {

enum FunName
{
  SEARCH = 0,
  LEAVE = 1,
  ATTACK = 2,
  MOVE = 3,
  SLEEP = 4,
  STATUS = 5,
  HELP = 6,
};

class Fun 
{
    std::map<std::string, FunName> mMapFun;
    std::map<std::string, int> mMapArgs;
    std::vector<std::string> mVecParam;

    void Search();
    void Leave();
    void Attack();
    void Move();
    void Sleep(Page* page, entity::Actor* player);
    void Status();
    void Help();

  public:
    Fun();
    ~Fun();

    int GetNumArg(std::string name);
    void ExecFunction(std::string name, std::vector<std::string>* params, Page* page,
        entity::Actor* player);
};

} // namespace utils