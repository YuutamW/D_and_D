// Dor Mandel :       ID: 315313825
// Yotam Weintraub:   ID: 321610859

#pragma once
#include <iostream>
#include "Item.hpp"

class Shield : public Item
{
    public:
    Shield(char* name) : Item(name, 0, 0, 5) {dedicatedChrctr = Any;}

    inline bool canPickUp(characterType charType) const override {return true;}
};
