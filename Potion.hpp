// Dor Mandel :       ID: 315313825
// Yotam Weintraub:   ID: 321610859

#pragma once
#include "Character.hpp"
using std::abs;
class Potion : public Item
{
public:
/*no need to override canpickup, no need to check dedicated character*/
    Potion(char* potionName, int HpBon = 0, int StrenBon = 0, int DfnsBon = 0 ) : Item(potionName,abs(HpBon),abs(StrenBon),abs(DfnsBon)) { dedicatedChrctr = Any;}
    virtual ~Potion() {}
    virtual Item* clone() const = 0;
    inline bool canPickUp(characterType /*charType*/) const override {return true;}
    inline std::string ItemCategory() const override {return std::string("POTION");}
};
