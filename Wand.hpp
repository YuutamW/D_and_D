// Dor Mandel :       ID: 315313825
// Yotam Weintraub:   ID: 321610859

#pragma once
#include <iostream>
#include "Item.hpp"

class Wand : public Item
{
    Wand(char *name) : Item(name, 0, 10, 0) {dedicatedChrctr = mage;}
    inline bool canPickUp(characterType charType) const override { return charType == dedicatedChrctr;}
};

