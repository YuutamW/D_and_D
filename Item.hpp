// Dor Mandel :       ID: 315313825
// Yotam Weintraub:   ID: 321610859

#pragma once
#include <iostream>
#include <cstring>
#include "Character.hpp"
#include "CharacterTypes.hpp"

class Item
{
private:
   char *name;
   int healthBonus;
   int strengthBonus;
   int defenseBonus;
protected:
    characterType dedicatedChrctr;
public:
    Item(char* itemName = nullptr, int HPBon = -1, int strenBon = -1, int defenseBon = -1 );
    virtual ~Item() = 0;
    virtual bool canPickUp(characterType charType) const { return true; }
    //getters
    inline int getHPBonus() const {return healthBonus; }
    inline int getStrenBonus() const {return strengthBonus;}
    inline int getDefenseBonus() const {return defenseBonus;}
    inline const std::string getName() const {return std::string(name);}
    
    inline bool operator!() const { return !name || healthBonus == -1 || strengthBonus == -1 || defenseBonus == -1 ;}

};

