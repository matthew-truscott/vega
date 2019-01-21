#include "actor.hpp"

using namespace entity;

Actor::Actor()
{
    mAlive = true;
}

Actor::~Actor()
{

}

bool Actor::IsAlive()
{
    return mAlive;
}

void Actor::Kill()
{
    mAlive = false;
}