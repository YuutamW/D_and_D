// Dor Mandel :       ID: 315313825
// Yotam Weintraub:   ID: 321610859

#pragma once
#include <iostream>
#include "Item.hpp"


class Sword : public Item
{
public:
    Sword(char* name, int HP = 0, int stren = 0, int dfns = 0) : Item(name,HP + 0,stren + 5,dfns + 10) {dedicatedChrctr = warrior;}
    inline bool canPickUp(characterType charType) const override { return charType == dedicatedChrctr;}
    inline Item* clone() const override {return new Sword(*this);}
    inline std::string ItemCategory() const override {return std::string("SWORD");}
};


