// Dor Mandel :       ID: 315313825
// Yotam Weintraub:   ID: 321610859

#include "Character.hpp"
#include <cstring>
#include <cmath>

#pragma region public funcs
    #pragma region cnstrctrs/dstrctrs
    Character::Character(char *chrName, int chrHP, int chrStren, int charDef)
    : name(strdup(chrName)) , health(chrHP), strength(chrStren), defense(charDef) {}

    

    Character::~Character()
    {
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
        int damageDealt = damage - defense;

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
            health += item.getHPBonus();
            strength += item.getStrenBonus();
            defense += item.getDefenseBonus();
        }
        return *this;
    }

   #pragma endregion

   
    #pragma endregion 