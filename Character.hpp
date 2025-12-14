//Yotam Weintraub 321610859
#pragma once
#include <iostream>
#include <cctype>
#include "Monster.hpp"

class Character
{
private:
    char *name;
    int health;
    int strength;
    int defense;
public:
    Character(/* args */);
    virtual ~Character();
};