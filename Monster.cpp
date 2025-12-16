// Dor Mandel :       ID: 315313825
// Yotam Weintraub:   ID: 321610859

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

Monster::Monster(const Monster& other) {*this = other;}

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
    int damageDealt = dmg - mnstrDef ;

    if(damageDealt <= 0) return;

    mnstrHP -= damageDealt; 
    if(damageDealt > mnstrHP) Defeated = true;
}

Monster &Monster::operator=(const Monster &other)
{
    if(this == &other) return *this;
    if(this->name) free(this->name);
    this->name = nullptr;
    this->name = (other.name) ? strdup(other.name) : nullptr;
    this->mnstrStren = other.mnstrStren;
    this->mnstrHP = other.mnstrHP;
    this->mnstrDef = other.mnstrDef;
    return *this;
}

#pragma endregion


