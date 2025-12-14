// Dor Mandel :       ID: 315313825
// Yotam Weintraub:   ID: 321610859

#pragma once
#include <iostream>
#include <cctype>
#include "Monster.hpp"
#include "Item.hpp"
class Monster;  //frwrd decleration
class Item;     //frwrd decleration

class Character
{
private:
    bool Alive = true;
    char *name;
    int health;
    int strength;
    int defense;
public:
    // Character();
    /*We need to come back here later and decide if we want to keep default params*/
    Character(char *chrName = nullptr, int chrHP = 0 , int chrStren = 0, int charDef = 0);
    void attack(Monster& target);
    void defend(int damage);
    inline bool isAlive() const {return Alive;}
    Character operator+(const Item& item);
    virtual ~Character() = 0;   //pure virtual
};