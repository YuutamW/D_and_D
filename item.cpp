// Dor Mandel :       ID: 315313825
// Yotam Weintraub:   ID: 321610859

#include "Item.hpp"
#pragma region public

    #pragma region destrctrs/dstrctrs
    Item::Item(char * itemName, int HPBon, int strenBon, int defenseBon)
    {
    name = (itemName) ? strdup(itemName) : nullptr;
    if(!name) {
        HPBon = strenBon = defenseBon = -1;
    }
    healthBonus = HPBon;
    strengthBonus = strenBon;
    defenseBonus = defenseBon;
    }

    Item::Item(const Item& other) :healthBonus(other.healthBonus), strengthBonus(other.strengthBonus),
     defenseBonus(other.defenseBonus), dedicatedChrctr(other.dedicatedChrctr) 
     {
        this->name = (other.name) ? strdup(other.name) : nullptr;
     }

    Item::~Item() {if(name)free(name); name = nullptr;}
    
    #pragma endregion

#pragma endregion