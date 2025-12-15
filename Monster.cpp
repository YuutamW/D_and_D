#include "Monster.hpp"
#include <cstring>
#include <iostream>

#pragma region Public
    #pragma region Constructors / Destructdor
Monster::Monster(char *mnstrName, int HP, int Stren, int Def)
{
    name = strdup(mnstrName);
    mnstrHP = HP;
    mnstrStren = Stren;
    mnstrDef = Def;

    Defeated = false;
}

Monster::~Monster()
{
    if(name){ free(name);name = nullptr;}
}
    #pragma endregion
    
void Monster::attack(Character &target)
{
    target.defend(mnstrStren);
}

void Monster::TakeDamage(int dmg)
{
    int damageDealt = dmg - mnstrDef;

    if(damageDealt <= 0) return;

    mnstrHP -= damageDealt; 
    if(damageDealt > mnstrHP) Defeated = true;
}

#pragma endregion


