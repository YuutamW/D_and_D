// Dor Mandel :       ID: 315313825
// Yotam Weintraub:   ID: 321610859

#pragma once
#include "Potion.hpp"

class DefensePotion : public Potion
{
public:
    DefensePotion(char* name, int HP = 0, int stren = 0, int dfns = 0) : Potion(name , HP , stren, dfns + 5) {}
    inline Item* clone() const override {return new DefensePotion(*this);}
};