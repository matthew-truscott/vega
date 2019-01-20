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
    std::string case_delimiter_cond;
    std::string case_goto_open;
    std::string case_goto_close;
    int gVerbose;

};

} // namespace project