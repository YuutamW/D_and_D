// Dor Mandel :       ID: 315313825
// Yotam Weintraub:   ID: 321610859

#pragma once
#include "Potion.hpp"

class StrengthPotion : public Potion
{

public:
    StrengthPotion(char* name, int HP = 0, int stren = 0, int dfns = 0) : Potion(name , HP , stren + 5, dfns ) {}
    inline Item* clone() const override {return new StrengthPotion(*this);}

};

