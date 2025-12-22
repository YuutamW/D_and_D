// Dor Mandel :       ID: 315313825
// Yotam Weintraub:   ID: 321610859

#include "Character.hpp"
#include <cstring>
#include <cmath>

#pragma region private Helpers

    bool Character::insertToInventory(const Item* itemToIn)
    {
        if(!itemToIn) return false;
        int itemIndex = 0;
        if(itemToIn->ItemCategory() == "POTION"){
            //if the item is a potion, we simply add the stats to the character stats.
            updateStats(itemToIn);
            //we arent using the potion any more and it isnt held in the inventory. the room will delete the item.
            return true;
        }
        else if(itemToIn->ItemCategory() == "SHIELD" && type == warrior)
        {
            itemIndex = 1;
        }
        else itemIndex = 0;
        return replaceItem(inventory[itemIndex], itemToIn);
    }

    bool Character::replaceItem(Item*& inventorySlot, const Item* itemToIn)
    {
        if(!itemToIn) return false;
        else if(!inventorySlot)
        {
            inventorySlot = itemToIn->clone();
            updateStats(itemToIn);
            return true;
        } 
        else if(*inventorySlot < *itemToIn)
        {
            health -= inventorySlot->getHPBonus();
            strength -= inventorySlot->getStrenBonus();
            defense -= inventorySlot->getDefenseBonus();
            delete inventorySlot;
            inventorySlot = itemToIn->clone();
            updateStats(inventorySlot);
            return true;
        }
        else {
            return false;
        }
    }

    void Character::updateStats(const Item *itemToIn)
    {
        if(!itemToIn) return;
        health += itemToIn->getHPBonus();
        strength += itemToIn->getStrenBonus();
        defense += itemToIn->getDefenseBonus();                           
    }

#pragma endregion

#pragma region public funcs
    #pragma region cnstrctrs/dstrctrs
    Character::Character(char *chrName, int chrHP, int chrStren, int charDef)
    : name(chrName ? strdup(chrName) : nullptr) , health(chrHP), strength(chrStren), defense(charDef) {}

    Character::Character(const Character& other) : name(other.name ? strdup(other.name) : nullptr),
    health(other.health), strength(other.strength), defense(other.defense), tookItem(other.tookItem), type(other.type)
    {
        for(int i = 0; i < NUM_OF_ITEMS_IN_INVENTOTY; i++)
            inventory[i] = (other.inventory[i]) ? other.inventory[i]->clone() : nullptr;
    }

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
        if(damage <= 0) return;
        int damageDealt = std::max(1, defense - damage);
        
        health -= damageDealt; 
        if(damageDealt > health) Alive = false;
    }
    
    #pragma region operators
    Character& Character::operator+(const Item &item)
    {
        if(!item) return *this;
        
        tookItem = (item.canPickUp(this->type)) ? insertToInventory(&item) : false;
        
        return *this;
    }
    
    #pragma endregion
    
    std::string Character::printPlayerStats() const
    {
        using namespace std;
        return "Player:  "+getName() +"\n\tHealth: " + to_string(health) + "\n\tStrength: " + to_string(strength) + "\n\tDefense: " + to_string(defense);
      
    }

    std::string Character::printInventory() const
    {
        using namespace std;
        string itemA = (inventory[0]) ? inventory[0]->printItem() : "N/A";
        string itemB = (inventory[1]) ? inventory[1]->printItem() : "N/A";
        return "\tInventory: \nItem 1: "  + itemA + "\nItem 2: " + itemB+"\n";
    }

#pragma endregion 