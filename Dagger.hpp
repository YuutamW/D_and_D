// Dor Mandel :       ID: 315313825
// Yotam Weintraub:   ID: 321610859

#pragma once
#include <iostream>
#include "Item.hpp"
class Dagger : public Item
{
public:
    Dagger(char* name) : Item(name , 0, 7, 3) {dedicatedChrctr = thief;}
    inline bool canPickUp(characterType charType) const override { return charType == dedicatedChrctr;}
};
