#pragma once

#include <string>
#include <vector>

namespace entity {

class Actor 
{
    bool mAlive;
    
  public:
    Actor();
    ~Actor();

    bool IsAlive();
    void Kill();
};

} // namespace utils