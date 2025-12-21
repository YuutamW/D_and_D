// Dor Mandel :       ID: 315313825
// Yotam Weintraub:   ID: 321610859

#pragma once
#include <iostream>
#include "Item.hpp"
class Dagger : public Item
{
public:
    Dagger(char* name, int HP = 0, int stren = 0, int dfns = 0) : Item(name , HP + 0,stren + 7,dfns + 3) {dedicatedChrctr = thief;}
    inline bool canPickUp(characterType charType) const override { return charType == dedicatedChrctr;}
    inline Item* clone() const override {return new Dagger(*this);}
    inline std::string ItemCategory() const override {return std::string("DAGGER");}
};
