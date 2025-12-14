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
    char *name;
    int health;
    int strength;
    int defense;
public:
    Character(char *chrName, int chrHP, int chrStren, int charDef);
    void attack(Monster& target);
    void defend(int damage);
    bool isAlive() const;
    Character operator+(const Item& item);
    virtual ~Character() = 0;   //pure virtual
};