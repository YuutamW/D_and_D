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
    void handleAdd(std::stringstream& ss);
    void handleConnect(std::stringstream& ss);
    void handlePlace(std::stringstream& ss);
    //---Gameplay helpers---
    void handleMove(std::string direction);
    void handleFight(std::string monsterName);
    void handlePickUp(std::string itemName);
public:
    Game(/* args */);
    ~Game();


    void loadFromFile(const std::string& filename);
    void executeCommands();
    void outputFinalState(const std::string& filename);
};


