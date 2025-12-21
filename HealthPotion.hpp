// Dor Mandel :       ID: 315313825
// Yotam Weintraub:   ID: 321610859

#pragma once
#include "Potion.hpp"

class HealthPotion : public Potion
{
private:
    /* data */
public:
    HealthPotion(char* name, int HP = 0, int stren = 0, int dfns = 0) : Potion(name , HP + 10, stren , dfns ) {}
    inline Item* clone() const override {return new HealthPotion(*this);}
    
};

