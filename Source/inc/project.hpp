#pragma once

#include <string>

namespace project {

class Global
{

  public:
    Global(int verbose);
    ~Global();

    std::string json_dir;
    std::string setting_delimiter_open;
    std::string setting_delimiter_close;
    std::string setting_delimiter_sep;
    int gVerbose;

};

} // namespace project