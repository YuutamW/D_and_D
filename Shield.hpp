// Dor Mandel :       ID: 315313825
// Yotam Weintraub:   ID: 321610859

#pragma once
#include <iostream>
#include "Item.hpp"

class Shield : public Item
{
    public:
    Shield(char* name, int HP = 0, int stren = 0, int dfns = 0) : Item(name,HP+ 0,stren+ 0,dfns+ 5) {dedicatedChrctr = warrior;}

    inline bool canPickUp(characterType charType) const override {return charType == warrior;}
    inline Item* clone() const override {return new Shield(*this);}
    inline std::string ItemCategory() const override {return std::string("SHIELD");}
};
