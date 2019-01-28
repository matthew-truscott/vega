#pragma once

#include <string>
#include <map>
#include <vector>

#include "page.hpp"
#include "actor.hpp"

namespace utils {


class Fun 
{
	//Now the mMapFun stores a string, a function pointer and args amount.
	//This imposes some limitations, now each function should have
	//the same arguments, but this should get rid of the switch statement.
	
	//TODO: Make some typedefs so everything is defined there, and then
	//		used anywhere else.
	
	typedef void (Fun::*FunFuncPointer)(std::vector<std::string>, Page*,
    entity::Actor*);//This typedef is for function pointers.
	
    std::map<std::string, std::pair<FunFuncPointer, unsigned int>> mMapFun;
    std::vector<std::string> mVecParam;
    
    void Search(std::vector<std::string>, Page*,
    entity::Actor*);
    void Leave(std::vector<std::string>, Page*,
    entity::Actor*);
    void Attack(std::vector<std::string>, Page*,
    entity::Actor*);
    void Move(std::vector<std::string>, Page*,
    entity::Actor*);
    void Sleep(std::vector<std::string>, Page* page, entity::Actor* player);
    void Status(std::vector<std::string>, Page*,
    entity::Actor*);
    void Help(std::vector<std::string>, Page*,
    entity::Actor*);

  public:
    Fun();
    ~Fun();

    unsigned int GetNumArg(std::string name);
    void ExecFunction(std::string name, std::vector<std::string>* params, Page* page,
        entity::Actor* player);
};

} // namespace utils
