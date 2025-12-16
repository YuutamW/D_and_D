// Dor Mandel :       ID: 315313825
// Yotam Weintraub:   ID: 321610859

#pragma once
#include <iostream>
#include "Item.hpp"

class Wand : public Item
{
    public:
    Wand(char* name, int HP = 0, int stren = 0, int dfns = 0) : Item(name,HP + 0,stren + 10,dfns + 0) {dedicatedChrctr = mage;}
    inline bool canPickUp(characterType charType) const override { return charType == dedicatedChrctr;}
    inline Item* clone() const override {return new Wand(*this);}
};

