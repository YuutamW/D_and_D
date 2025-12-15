// Dor Mandel :       ID: 315313825
// Yotam Weintraub:   ID: 321610859

#include "Item.hpp"
#pragma region public

    #pragma region destrctrs/dstrctrs
    Item::Item(char * itemName, int HPBon, int strenBon, int defenseBon)
    {
    name = strdup(itemName);
    healthBonus = HPBon;
    strengthBonus = strenBon;
    defenseBonus = defenseBon;
    }

    Item::~Item() {if(name)free(name); name = nullptr;}
    
    #pragma endregion

#pragma endregion