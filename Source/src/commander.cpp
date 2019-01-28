#include <iostream>
#include <fstream>
#include <algorithm>

#include "commander.hpp"
#include "filepath.h"

using namespace text;

Commander::Commander(project::Global* g)
{
    mG = g;

    // read in JSON file (see nlohmann library)
    std::string filePath = "../../" + mG->json_dir + "/" + filepath::getCommandsFile();

    json tJson;

    std::ifstream cmdFile(filePath);
    if (!cmdFile) 
    {
        std::cout << "The file doesn't exist!\n";
        std::cout << "Exiting gracefully...\n"; // handle this in the future
        return;
    }

    cmdFile >> tJson;

    mMapCmd = tJson.get<std::map<std::string, std::string>>();

    // read in JSON file (see iteration access) for parameter map
    filePath = "../../" + mG->json_dir + "/" + filepath::getItemsFile();

    tJson.clear();

    std::ifstream parFile(filePath);
    if (!parFile)
    {
        std::cout << "The file doesn't exist!\n";
        std::cout << "Exiting gracefully...\n"; // handle this in the future
        return;
    }

    parFile >> tJson;

    for (json::iterator iter = tJson.begin(); iter != tJson.end(); ++iter)
    {
        std::string tKey = iter.key();
        Item tPar = iter.value().get<Item>();

        mMapPar.insert({tKey, tPar});
    }

    
}

Commander::~Commander()
{}

std::string Commander::getFunction(std::string command)
{
    std::transform(command.begin(), command.end(), command.begin(), ::tolower);
    std::string oCmdFun;

    for (std::map<std::string, std::string>::iterator iter = mMapCmd.begin();
         iter != mMapCmd.end();
         ++iter)
    {
        std::string tCmdKey = iter->first;
        std::string tCmdFun = iter->second;
        size_t cmdmatch = command.find(tCmdKey);
        if (cmdmatch != std::string::npos)
        {
            oCmdFun = tCmdFun;
            break;
        }
    }

    if (mG->gVerbose > 0)
    {
        if (oCmdFun.empty()) std::cout << "no fun match found for " << command << "\n";
        else std::cout << "match found, command: " << oCmdFun << "\n";
    }

    return oCmdFun;
}

std::vector<std::string> Commander::getParameters(std::string command)
{
    std::transform(command.begin(), command.end(), command.begin(), ::tolower);
    std::vector<std::string> oVecPar;

    for (std::map<std::string, Item>::iterator iter = mMapPar.begin();
         iter != mMapPar.end();
         ++iter)
    {
        std::string tCmdKey = iter->first;
        size_t cmdmatch = command.find(tCmdKey);
        if (cmdmatch != std::string::npos)
        {
            oVecPar.push_back(tCmdKey);
        }
    }

    if (mG->gVerbose > 0)
    {
        if (oVecPar.empty()) std::cout << "no par match found for " << command << "\n";
        else std::cout << "match found, param: ";
        for (auto iter = oVecPar.begin(); iter != oVecPar.end(); ++iter)
        {
            std::cout << *iter << " ";
        }
        std::cout << "\n";
    }

    return oVecPar;
}

void Commander::printFunctions()
{
    std::cout << "FUNCTION LIST:\n";
    for (auto it = mMapCmd.cbegin(); it != mMapCmd.cend(); ++it)
    {
        std::cout << it->first << " " << it->second << "\n";
    }
}

void Commander::printParameters()
{        
    std::cout << "PARAMETER LIST:\n";
    for (auto it = mMapPar.cbegin(); it != mMapPar.cend(); ++it)
    {
        std::cout << it->first << " " << it->second.sDescription << "\n";
    }
}

namespace text {
    
void to_json(json& j, const Item& i)
{
    j = json{{"description", i.sDescription}};
}

void from_json(const json& j, Item& i)
{
    j.at("description").get_to(i.sDescription);
}

} // namespace text
