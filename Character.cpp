//DORRRR!!!! PUT OUR NAMESSSS HEEEREE!!!!!
#include "Character.hpp"
#include <cstring>
#include <cmath>

#pragma region public funcs
    #pragma region cnstrctrs/dstrctrs
    Character::Character(char *chrName, int chrHP, int chrStren, int charDef)
    : name(strdup(chrName)) , health(chrHP), strength(chrStren), defense(charDef) {}

    Character::~Character() {if(name) free(name); name = nullptr;}
    
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

    /*
    A.o A.hpp
    B.cpp B.hpp 
    C.cpp C.hpp
    Main.cpp

    A-> Fuck! 
    Main _A->F; 

    _A->F; ->F-A.cpp

    A->inline FUCK! 


    attack(15);
    attack(7);



    */

    external bool Character::isAlive()
    {

    }

    #pragma endregion 