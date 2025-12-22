// Dor Mandel :       ID: 315313825
// Yotam Weintraub:   ID: 321610859

#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "Dungeon.hpp"
#include "Character.hpp"
#include "CharacterTypes.hpp"
#include "Room.hpp"
#include "Item.hpp"
#include "Warrior.hpp"
#include "Mage.hpp"
#include "Thief.hpp"
#include "Sword.hpp"
#include "Shield.hpp"
#include "Wand.hpp"
#include "Dagger.hpp"
#include "HealthPotion.hpp"
#include "StrengthPotion.hpp"
#include "DefensePotion.hpp"
class Game
{
private:
    Dungeon dungeon;
    Character* player = nullptr;
    Room* currentRoom = nullptr;
    //string vector to store executions later
    std::vector<std::string> pendingCommands;
    //string vector to log actions
    std::vector<std::string> actionLog;
    
    
    //--Parsing--
    void parseLine(const std::string& line);
    //--execution--
    void handleCreate(std::stringstream& ss);
    // void handleAdd(std::stringstream& ss); //Add command has been removed from requirements
    void handleConnect(std::stringstream& ss);
    void handlePlace(std::stringstream& ss);
    //---Gameplay helpers---
    void handleMove(std::string direction);
    void handleFight(std::string monsterName);
    void handlePickUp(std::string itemName);

    enum errTypes 
    {
        ROOM411,
        ROOM_ALREADY_EXISTS,
        INVALID_COMMAND_ARG,
        NEW_ROOM_FAIL,
        NEW_ITEM_FAIL,
        NEW_MONSTER_FAIL,
        PLAYER_CREATE_FAIL,
        INVALID_CREATE_ARG,
        INVALID_DIR_ARG,
        INVALID_ITEM_TYPE,
        ITEM_ALREADY_IN_ROOM,
        PLACE_ITEM_FAIL,
    };
    
    void outputError(std::string errVar, errTypes errType);
    inline std::string roomNotFoundErr(std::string roomName) const {return "ERROR! room:  "+ roomName+" Not Found";}
    inline bool validateDirArg(std::string DIR) const {return (DIR=="North"||DIR=="South"||DIR=="West"||DIR=="East");}
    public:
    Game(/* args */);
    ~Game();


    void loadFromFile(const std::string& filename);
    void executeCommands();
    void outputFinalState(const std::string& filename);
};


