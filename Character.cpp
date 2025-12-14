//DORRRR!!!! PUT OUR NAMESSSS HEEEREE!!!!!
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
        //we havent implemented getters and setters for Monster, so we will write for now psuedoCode:
        /*
            target.TakeDamage(this->strength);
        */
    }

    void Character::defend(int damage)
    {
        int damageDealt = defense - damage;

        if(damageDealt <= 0) return;

        health -= damageDealt; 
        if(damageDealt > health) Alive = false;
    }

   #pragma region operators
    Character& Character::operator+(const Item &item)
    {
        // if(!item) return *this;
        // this->defense += item.defenseBonus;
        // this->strength += item.attackBonus;
        // this->health += item.healthBonus;
        
        return *this;
    }

   #pragma endregion

   
    #pragma endregion 