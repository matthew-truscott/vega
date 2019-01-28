#include "fun.hpp"

#include <utility>
#include <iostream>

//Used for.. calling member function of an object by function pointer.
#define CALL_MEMBER_FN(object,ptrToMember)  ((object).*(ptrToMember))

using namespace utils;

Fun::Fun()
{
	//						std::make_pair(&func_name, args count);
    mMapFun["search"] =		std::make_pair(&Search, 1);
    mMapFun["leave"] =		std::make_pair(&Leave, 0);
    mMapFun["attack"] =		std::make_pair(&Attack, 1);
    mMapFun["move"] =		std::make_pair(&Move, 1);
    mMapFun["sleep"] =		std::make_pair(&Sleep, 0);
    mMapFun["status"] =		std::make_pair(&Status, 0);
    mMapFun["help"] =		std::make_pair(&Help, 0);
}

Fun::~Fun()
{

}

void Fun::Search(std::vector<std::string> params, Page* page,
    entity::Actor* player)
{
    std::cout << "Called Fun::Search, params_size=" << params.size() << std::endl;
}

void Fun::Leave(std::vector<std::string> params, Page* page,
    entity::Actor* player)
{
    std::cout << "Called Fun::Leave, params_size=" << params.size() << std::endl;
}

void Fun::Attack(std::vector<std::string> params, Page* page,
    entity::Actor* player)
{
    std::cout << "Called Fun::Attack, params_size=" << params.size() << std::endl;
}

void Fun::Move(std::vector<std::string> params, Page* page,
    entity::Actor* player)
{
    std::cout << "Called Fun::Move, params_size=" << params.size() << std::endl;
}


void Fun::Sleep(std::vector<std::string> params, Page* page, entity::Actor* player)
{
    std::cout << "Called Fun::Sleep, params_size=" << params.size() << std::endl;
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


void Fun::Status(std::vector<std::string> params, Page* page,
    entity::Actor* player)
{
    std::cout << "Called Fun::Status, params_size=" << params.size() << std::endl;
}

void Fun::Help(std::vector<std::string> params, Page* page,
    entity::Actor* player)
{
    std::cout << "Called Fun::Help, params_size=" << params.size() << std::endl;
}



unsigned int Fun::GetNumArg(std::string name)
{
    return mMapFun[name].second;
}

void Fun::ExecFunction(std::string name, std::vector<std::string>* params, Page* page,
    entity::Actor* player)
{
	//Trying to find function name in the map, if found -- call,
	//if not -- do nothing.
	
    std::map<std::string, std::pair<FunFuncPointer, unsigned int>>::iterator it = mMapFun.find(name);
    
    if(it != mMapFun.end())
    	CALL_MEMBER_FN( *this, ( mMapFun[name].first ) )( *params, page, player );//This is a macro defined at the top of this file.
    	
    
    return;
}
