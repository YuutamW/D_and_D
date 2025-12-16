// Dor Mandel :       ID: 315313825
// Yotam Weintraub:   ID: 321610859

#pragma once

#include <iostream>
#include "Character.hpp"



class Monster
{
private:
    char *name;
    int mnstrHP;
    int mnstrStren;
    int mnstrDef;
    bool Defeated = false;
    
public:
    Monster(char* mnstrName = nullptr, int HP = 0 , int Stren = 0 , int Def = 0);
    Monster(const Monster& other);
    ~Monster();

    void attack(Character& target);
    inline bool isDefeated(){return Defeated;}

    // Helper
    void TakeDamage(int dmg);
    inline bool operator!() const
    {return (!name || mnstrHP == -1 || mnstrStren == -1 || mnstrDef == -1);}

    inline const int getHPBonus() const {return mnstrHP; }
    inline const int getStrenBonus() const {return mnstrStren;}
    inline const int getDefenseBonus() const {return mnstrDef;}
    inline const std::string getStrName() const {return std::string(name);}
    inline const char* getName() const {return name;}
    //Operators overloading
    Monster& operator=(const Monster& other);
    /* Monster* operator=(const Monster* other); */
    inline bool operator==(const Monster& other) const
    {return (!other) ? false : (strcmp(this->name,other.name) == 0) && (this->mnstrStren == other.mnstrStren) && (this->mnstrDef == other.mnstrDef);}

};

