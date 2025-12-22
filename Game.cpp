// Dor Mandel :       ID: 315313825
// Yotam Weintraub:   ID: 321610859

#include "Game.hpp"
using namespace std;
#pragma region destrctrs/cnstrcrs

    Game::~Game(){
        if(player) delete player;
        player = nullptr; //Dungeon destructor automatically cleans up rooms
    }

#pragma endregion

#pragma region private helpers

    void Game::parseLine(const string& line )
    {
        if(line.empty() || line.substr(0,2) == "//") return; //skip comment/empty
        stringstream ss(line);
        string command;
        ss >> command;
        //Setup commands - executed immediatly
        if(command == "Create" || command == "create")
        handleCreate(ss);
                    // else if(command == "Add" || command == "add")
                    // handleAdd(ss);
        else if(command == "Connect" || command == "connect")
        handleConnect(ss);
        else if(command == "Place" || command == "place")
        handlePlace(ss);
        else if(command == "Set" || command == "set")
        {
            string subCmd , roomName;
            ss >> subCmd >> roomName;
            if(subCmd == "StartRoom") {
                Room* startRoomToSet = dungeon.findRoom(roomName);
                if(!startRoomToSet || !dungeon.getState())
                {
                    outputError(roomName,ROOM411);
                    return;
                }
                else dungeon.setStartRoom(startRoomToSet);
            }
        }
        else if(command == "Enter" || command == "Move" || 
             command == "Fight" || command == "PickUp")
             {//storing the line to be executed in phase 2
                pendingCommands.push_back(line);
             }
        else outputError(command, INVALID_COMMAND_ARG);
    }

    void Game::handleCreate(stringstream& ss)
    {
        string type, name;
        ss >> type >> name;
        //---check what to create:---
        if(type == "Room"){
            //check if the room is already in the dungeon
            Room* newRoom = dungeon.findRoom(name);
            if(newRoom || dungeon.getState()){
                outputError(name,ROOM_ALREADY_EXISTS);
                return;
            }else{
                //create and add the room
                newRoom = new Room(name.c_str());
                if(!newRoom) {
                    outputError(name,NEW_ROOM_FAIL);
                    return;
                }
                dungeon.addRoom(newRoom);
            }
        }else if(type == "Warrior" || type == "warrior")//character creation
        {
            player = new Warrior((char*)name.c_str());
            if(!player) {outputError(name, PLAYER_CREATE_FAIL);return;}
            else if(!(*player)) {outputError(name, PLAYER_CREATE_FAIL);return;}
        }else if(type == "Thief" || type =="thief")
        {
            player = new Thief((char*)name.c_str());
            if(!player) {outputError(name, PLAYER_CREATE_FAIL);return;}
            else if(!(*player)) {outputError(name, PLAYER_CREATE_FAIL);return;}
        }else if(type == "Mage" || type == "mage")
        {
            player = new Mage((char*)name.c_str());
            if(!player) {outputError(name, PLAYER_CREATE_FAIL);return;}
            else if(!(*player)) {outputError(name, PLAYER_CREATE_FAIL);return;}
        }
        else {outputError(type,INVALID_CREATE_ARG); }
    }

    void Game::handleConnect(stringstream& ss)
    {
        string roomA,roomB,direction;
        ss >> roomA >> roomB >> direction;
        Room* rA = dungeon.findRoom(roomA);
        if(!rA || !dungeon.getState()){outputError(roomA,ROOM411); return;}
        Room* rB = dungeon.findRoom(roomB);
        if(!rB || !dungeon.getState()) {outputError(roomB,ROOM411); return;}
        if(validateDirArg(direction) == false)
        {outputError(direction,INVALID_DIR_ARG); return;}
        dungeon.connectRooms(rA, rB, direction);
    }

    void Game::handlePlace(stringstream& ss)
    {
        string type;
        ss >> type; //<Place> "Item" or "Monster"?
        if(type == "Item")
        {
            string itemName,roomName;
            int hp,str,def;
            ss >> itemName >> roomName >> hp >> str >> def;
            char* itemC_Name = (char*)itemName.c_str();
            Room* itemRoom = dungeon.findRoom(roomName);
            if(!itemRoom || !dungeon.getState()) {outputError(roomName,ROOM411);return;}
            else if(itemRoom->getItem() != nullptr){outputError(roomName,ITEM_ALREADY_IN_ROOM);return;}
            Item* newItem = nullptr;
            if(itemName == "Sword") newItem = new Sword(itemC_Name,hp,str,def);
            else if(itemName == "Shield") newItem = new Shield(itemC_Name,hp,str,def);
            else if(itemName == "Wand") newItem = new Wand(itemC_Name,hp,str,def);
            else if(itemName == "Dagger") newItem = new Dagger(itemC_Name,hp,str,def);
            else if(itemName == "HealthPotion") newItem = new HealthPotion(itemC_Name,hp,str,def);
            else if(itemName == "DefensePostion") newItem = new DefensePotion(itemC_Name,hp,str,def);
            else if(itemName == "StrengthPotion") newItem = new StrengthPotion(itemC_Name,hp,str,def);
            else {outputError(itemName,INVALID_ITEM_TYPE); return;}

            if(newItem){
                dungeon.placeItem(roomName, newItem);
                if(!dungeon.getState()) {
                    outputError(itemName,PLACE_ITEM_FAIL);
                    delete newItem;
                    return;
                }
            }

        }
        else if(type == "Monster")
        {
            string monstName, roomName;
            int hp,str,def;
            ss >> monstName >> roomName >> hp >> str >> def;
            Room* monstRoom = dungeon.findRoom(roomName);
            if(!monstRoom) {outputError(roomName, ROOM411); return;}
            Monster* newMonster = new Monster((char*)monstName.c_str(),hp,str,def);
            dungeon.placeMonster(roomName,newMonster);
            if(!dungeon.getState()) {
                outputError(monstName, NEW_MONSTER_FAIL);
                if(newMonster) delete newMonster;
                return;
            }
        }
        else {outputError(type,INVALID_COMMAND_ARG); return;}
    }

    void Game::handleMove(string direction)
    {
        if(!currentRoom) return;
        if(!validateDirArg(direction)) {outputError(direction,INVALID_DIR_ARG); return ;}
        Room* nextRoom = nullptr;
        if(direction == "North") nextRoom = currentRoom->getNorth();
        else if(direction == "South") nextRoom = currentRoom->getSouth();
        else if(direction == "East") nextRoom = currentRoom->getEast();
        else if(direction == "West") nextRoom = currentRoom->getWest();
        if (nextRoom) {
        currentRoom = nextRoom;
        actionLog.push_back(player->getName() + " moves " + direction + " to " + currentRoom->getName() + ".");
        }
        else actionLog.push_back("Move failed: No connection " + direction + ".");
    
    }

#pragma endregion