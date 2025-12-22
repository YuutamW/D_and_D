// Dor Mandel :       ID: 315313825
// Yotam Weintraub:   ID: 321610859

#pragma once

#include <iostream>
#include "Character.hpp"
#include <cstring>
class Character;


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

    
    inline int getHPBonus() const {return mnstrHP; }
    inline int getStrenBonus() const {return mnstrStren;}
    inline int getDefenseBonus() const {return mnstrDef;}
    inline const std::string getStrName() const {return std::string(name);}
    inline const char* getName() const {return name;}
    std::string printMonster() const;
    //Operators overloading
    Monster& operator=(const Monster& other);
    //! op: will return true when (name == null) or detected the less critical error data(-1) that could have been set along the program.
    inline bool operator!() const {return (!name || (mnstrDef*mnstrHP*mnstrStren) == -1);}
    //==op: will return true when all data are the same. NOTE: will return false if (other) is a bad argument.
    bool operator==(const Monster& other) const;
    // {return (!other) ? false : ((strcmp(this->name,other.name) == 0) && (this->mnstrStren == other.mnstrStren) && (this->mnstrDef == other.mnstrDef));}

};

