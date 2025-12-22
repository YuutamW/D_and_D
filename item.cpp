// Dor Mandel :       ID: 315313825
// Yotam Weintraub:   ID: 321610859

#include "Item.hpp"
#pragma region public

    #pragma region destrctrs/dstrctrs
Item::Item(char *itemName, int HPBon, int strenBon, int defenseBon)
{
    name = (itemName) ? strdup(itemName) : nullptr;
    if(!name || HPBon<0 || strenBon<0 || defenseBon<0) {
        HPBon = strenBon = defenseBon = -1;
    }
    healthBonus = HPBon;
    strengthBonus = strenBon;
    defenseBonus = defenseBon;
    itemStats = healthBonus+strengthBonus+defenseBonus;
}

Item::Item(const Item& other) :healthBonus(other.healthBonus), strengthBonus(other.strengthBonus),
defenseBonus(other.defenseBonus), dedicatedChrctr(other.dedicatedChrctr) 
{
    this->name = (other.name) ? strdup(other.name) : nullptr;
}
Item::~Item() {if(name)free(name); name = nullptr;}
    
#pragma endregion
    
    #pragma region printMethods
    std::string Item::printItem() const
    {
        using namespace std;
        return getName() +" "+ to_string(healthBonus) +" "+ to_string(strengthBonus)+" "+ to_string(defenseBonus);
    }

    #pragma endregion

    #pragma region Operators
    bool Item::operator==(const Item & other) const
    {
        return (!*this || !other ) ? false : this->itemStats == other.itemStats;
    }

    bool Item::operator>(const Item & other) const  
    {
        return (!*this || !other) ? false : this->itemStats > other.itemStats;
    }

    bool Item::operator<(const Item & other) const
    {
        return (!*this || !other) ? false : !(*this > other) ;
    }

    
    #pragma endregion

#pragma endregion