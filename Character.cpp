// Dor Mandel :       ID: 315313825
// Yotam Weintraub:   ID: 321610859

#include "Character.hpp"
#include <cstring>
#include <cmath>

#pragma region private Helpers

    void Character::insertToInventory(const Item* itemToIn)
    {
        if(!itemToIn) return;
        Item* inventoryItem;
        if(itemToIn->ItemCategory() == "POTION"){
        //if the item is a potion, we simply add the stats to the character stats.
            updateStats(itemToIn);
            delete itemToIn;    //we arent using the potion any more and it isnt held in the inventory.
            return;
        }
        else if(itemToIn->ItemCategory() == "SHIELD" && type == warrior)
        {
            inventoryItem =  inventory[1];
        }
        else inventoryItem = inventory[0];
        replaceItem(inventoryItem, itemToIn);
    }

    void Character::replaceItem(const Item* inventoryItem, const Item *itemToIn)
    {
        if(!itemToIn) return;
        else if(!inventoryItem)
        {
            inventoryItem = itemToIn;
            updateStats(itemToIn);
            return;
        } 
        else if(*inventoryItem < *itemToIn)
        {
            health -= inventoryItem->getHPBonus();
            strength -= inventoryItem->getStrenBonus();
            defense -= inventoryItem->getDefenseBonus();
            delete inventoryItem;
            inventoryItem = nullptr;
        }
        else {
            delete itemToIn;
            return;
        }
        inventoryItem = itemToIn;
        updateStats(itemToIn);
    }

#pragma endregion

#pragma region public funcs
    #pragma region cnstrctrs/dstrctrs
    Character::Character(char *chrName, int chrHP, int chrStren, int charDef)
    : name(chrName ? strdup(chrName) : nullptr) , health(chrHP), strength(chrStren), defense(charDef) {}

    

    Character::~Character()
    {
        for(int i = 0; i < NUM_OF_ITEMS_IN_INVENTOTY;i++)
        {
            if(inventory[i]) delete inventory[i];
            inventory[i] = nullptr;
        }
        if (name)
            free(name);
        name = nullptr;
    }

#pragma endregion

    void Character::attack(Monster &target)
    {
       target.TakeDamage(strength);
    }

    void Character::defend(int damage)
    {
        int damageDealt = std::max(1, damage - defense);

        if(damageDealt <= 0) return;

        health -= damageDealt; 
        if(damageDealt > health) Alive = false;
    }

   #pragma region operators
    Character& Character::operator+(const Item &item)
    {
        if(!item) return *this;

        if(item.canPickUp(this->type))
        {
            insertToInventory(&item);
        }
        return *this;
    }

   #pragma endregion

   
    #pragma endregion 