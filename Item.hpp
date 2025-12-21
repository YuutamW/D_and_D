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
   int itemStats;
protected:
    characterType dedicatedChrctr;
public:
    Item(char* itemName , int HPBon = 0, int strenBon = 0, int defenseBon = 0 );
    virtual ~Item() = 0;
    virtual bool canPickUp(characterType charType) const { return true; }
    virtual Item* clone() const = 0;
    Item(const Item& other);
    //getters
    inline int getHPBonus() const {return healthBonus; }
    inline int getStrenBonus() const {return strengthBonus;}
    inline int getDefenseBonus() const {return defenseBonus;}
    inline const std::string getName() const {return std::string(name);}
    virtual std::string ItemCategory() const = 0;
    std::string printItem() const;
    //operators
    inline bool operator!() const { return !name || healthBonus == -1 || strengthBonus == -1 || defenseBonus == -1 ;}
    //OP==: (Item)==(char*) compares names
    inline bool operator==(const char* otherItemName) const {return (otherItemName)?  strcmp(this->name,otherItemName) == 0 : false;}
    //OP==: (Item)==(OtherItem) only compares stats and not names.
    bool operator==(const Item& other) const;
    bool operator>(const Item& other) const;
    bool operator<(const Item& other) const;
};

