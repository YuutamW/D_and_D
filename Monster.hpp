// Dor Mandel :       ID: 315313825
// Yotam Weintraub:   ID: 321610859

#pragma once

#include <iostream>

class Character;    //fwd_Decleration

class Monster
{
private:
    char *name;
    int mnstrHP;
    int mnstrStren;
    int mnstrDef;
    bool Defeated = false;
    
public:
    Monster(char* mnstrName = nullptr, int HP = -1 , int Stren = -1 , int Def = -1);
    ~Monster();

    void attack(Character& target);
    inline bool isDefeated(){return Defeated;}

    // Helper
    void TakeDamage(int dmg);
    bool operator!() const
    {return (!name || mnstrHP == -1 || mnstrStren == -1 || mnstrDef == -1);}

};

