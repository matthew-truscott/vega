#pragma once

#include <string>
#include <map>
#include <nlohmann/json.hpp>

#include "project.hpp"

using json = nlohmann::json;

namespace text {

struct Item
{
    std::string sDescription;
};

class Commander 
{
    std::map<std::string, std::string> mMapCmd;
    std::map<std::string, Item> mMapPar;
    project::Global* mG;
    
  public:
    Commander(project::Global* g);
    ~Commander();

    std::string getFunction(std::string command);
    std::vector<std::string> getParameters(std::string command);

    void printFunctions();
    void printParameters();
};

void to_json(json& j, const Item& i);
void from_json(const json& j, Item& i);

} // namespace text