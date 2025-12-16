// Dor Mandel :       ID: 315313825
// Yotam Weintraub:   ID: 321610859

#pragma once

#include <iostream>
#include "Character.hpp"

class Character;    //fwd_Decleration

class Monster
{
private:
    char *name;
    int mnstrHP;
    int mnstrStren;
    int mnstrDef;
    bool Defeated = false;
    
public:
    Monster(char* mnstrName = nullptr, int HP = -1 , int Stren = -1 , int Def = -1);
    Monster(const Monster& other);
    ~Monster();

    void attack(Character& target);
    inline bool isDefeated(){return Defeated;}

    // Helper
    void TakeDamage(int dmg);
    bool operator!() const
    {return (!name || mnstrHP == -1 || mnstrStren == -1 || mnstrDef == -1);}

    inline int getHPBonus() const {return mnstrHP; }
    inline int getStrenBonus() const {return mnstrStren;}
    inline int getDefenseBonus() const {return mnstrDef;}
    inline const std::string getName() const {return std::string(name);}

    //assign oprtr Overlaod
    Monster& operator=(const Monster& other);

};

