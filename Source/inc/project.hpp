#pragma once

#include <string>

namespace project {

class Global
{

  public:
    Global(int verbose);
    ~Global();

    std::string json_dir;
    int gVerbose;

};

} // namespace project