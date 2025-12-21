// Dor Mandel :       ID: 315313825
// Yotam Weintraub:   ID: 321610859

#pragma once
#include <iostream>
#include <cctype>
#include "Monster.hpp"
#include "Item.hpp"
#define NUM_OF_ITEMS_IN_INVENTOTY 2
//frwrd decleration
class Monster;  
class Item;     

class Character
{
private:
    bool Alive = true;
    char *name;
    int health;
    int strength;
    int defense;
    Item *inventory[NUM_OF_ITEMS_IN_INVENTOTY] = {nullptr};
    void insertToInventory(const Item *itemToIn);
    void replaceItem(const Item* inventoryItem ,const Item *itemToIn);
    inline void updateStats(const Item* itemToIn) 
    {if(!itemToIn) return;
    health += itemToIn->getHPBonus();
    strength += itemToIn->getStrenBonus();
    defense += itemToIn->getDefenseBonus();}
    protected :
    characterType type;
public:
    // Character();
    /*We need to come back here later and decide if we want to keep default params*/
    Character(char *chrName , int chrHP = 0 , int chrStren = 0, int charDef = 0);
    void attack(Monster& target);
    void defend(int damage);
    inline bool isAlive() const {return Alive;}
    Character& operator+(const Item& item);
    virtual ~Character() = 0;   //pure virtual
    
    
    
    //getters
    inline int getHPBonus() const {return health; }
    inline int getStrenBonus() const {return strength;}
    inline int getDefenseBonus() const {return defense;}
    inline const std::string getName() const {return std::string(name);}
};