// Dor Mandel :       ID: 315313825
// Yotam Weintraub:   ID: 321610859

#include "Monster.hpp"
#include <cstring>
#include <iostream>

#pragma region Public
    #pragma region Constructors / Destructdor

Monster::Monster(char *mnstrName, int HP, int Stren, int Def) : Defeated(false)
{
     
    name = (mnstrName) ? strdup(mnstrName) : nullptr;
    if(!name) {HP = Stren = Def = -1;} //this is a safety flag that the ! operator will catch, whether no name was given or strdup failed.
    mnstrHP = HP;
    mnstrStren = Stren;
    mnstrDef = Def;

    
}

Monster::Monster(const Monster& other) : name(nullptr) {*this = other;}

Monster::~Monster()
{
    if(name){ free(name);name = nullptr;}
}
    
    #pragma endregion cnstrctrs/dstrctrs

void Monster::attack(Character &target)
{
    target.defend(mnstrStren);
}

void Monster::TakeDamage(int dmg)
{
    if(Defeated) return;
    int damageDealt = std::max(1, dmg - mnstrDef );

    // if(damageDealt <= 0) return;
    if(damageDealt > mnstrHP) Defeated = true;
    mnstrHP -= damageDealt; 
}

    #pragma region operator overlaoding
Monster &Monster::operator=(const Monster &other)
{
    if(this == &other || *this == other) return *this;//using == operator to check if they are same stats exactly, or regular== op between pointers.
    if(this->name) free(this->name);
    this->name = nullptr;
    this->name = (other.name) ? strdup(other.name) : nullptr;
    if(!name) {this->mnstrStren = this->mnstrHP = this->mnstrDef = -1;}//load with error data so that the ! operator overload func could catch
    else {
    this->mnstrStren = other.mnstrStren;
    this->mnstrHP = other.mnstrHP;
    this->mnstrDef = other.mnstrDef;
    }
    return *this;
}

bool Monster::operator==(const Monster &other) const
{
    return (strcmp(this->name,other.name) == 0 && 
    this->mnstrStren == other.mnstrStren &&
     this->mnstrDef == other.mnstrDef);
}

// bool operator!() const {return (!name || (mnstrDef*mnstrHP*mnstrStren) == -1 || Defeated);}

/*
Monster *Monster::operator=(const Monster *other)
{   if(!other) return this;
    if(!(*other) || this == other) return this;
    *this = *other;
    return this;
}
*/

    #pragma endregion operator overlaoding

#pragma endregion Public


