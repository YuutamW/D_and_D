// Dor Mandel :       ID: 315313825
// Yotam Weintraub:   ID: 321610859

#include "Game.hpp"
using namespace std;
#pragma region destrctrs/cnstrcrs

    Game::Game() {}

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
            if(newRoom){
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

    void Game::handleFight(string monsterName)
    {
        if(!currentRoom) return;
        Monster* monster = (Monster*)currentRoom->getMnstr();//check if monster is in room
        if(!monster || monster->getName() != monsterName) {
            actionLog.push_back(monsterName + "Not found in room :" +currentRoom->getName());
            return;
        }
        actionLog.push_back(player->getName() + " fights " + monsterName);
        while(player->isAlive() && !monster->isDefeated())
        {
            player->attack(*monster);
            actionLog.push_back("\t"+player->getName() + " Attacks: "+ monsterName +" monster HP: " + to_string(monster->getHPBonus()));

            if(!monster->isDefeated()) {
                monster->attack(*player);
                actionLog.push_back("\t"+monster->getStrName() + " Attacks: "+ player->getName() +" Player HP: " + to_string(player->getHPBonus()));
            }
        }
        if (player->isAlive()) {
        actionLog.push_back(player->getName() + " fights " + monsterName + ": Victory");
        } else {
        actionLog.push_back(player->getName() + " fights " + monsterName + ": Lose");
        }
    }

    void Game::handlePickUp(string itemName)
    {
        if(!currentRoom || !player) return;

        Item* item = (Item*)currentRoom->getItem();

        if(!item || item->getName() != itemName){
            actionLog.push_back(itemName+" Does not exist in current room: "+currentRoom->getName());
            return;
        }
        *player + *item;
        if(player->ItemTaken()) {
            actionLog.push_back(player->getName()+" picks up " + itemName );
        }
        else {
            actionLog.push_back(itemName+ " Has not been picked up: ");
            if(item->canPickUp(player->getCharacterType()))
            {
                actionLog.push_back(itemName+" Stats are worse than current item");
            }
            else{
                actionLog.push_back(itemName+" cannot be picked up by "+player->getName());
            }
        }
        currentRoom->setItem(nullptr); //inventory keepsa deep cpy, delete from room 
        //to prevent picking up again, or if didnt pick up, it isnt used.
    }

    void Game::outputError(string errVar, errTypes errType)
{
    string msg = "Error: ";
    
    switch(errType)
    {
        case ROOM411:

            msg += "Room '" + errVar + "' was not found in the dungeon.";
            break;

        case ROOM_ALREADY_EXISTS:
            msg += "Attempted to create Room '" + errVar + "', but it already exists.";
            break;

        case INVALID_COMMAND_ARG:
            msg += "Unrecognized command or argument: " + errVar;
            break;

        case NEW_ROOM_FAIL:
            msg += "Memory allocation failed. Could not create Room: " + errVar;
            break;

        case NEW_ITEM_FAIL:
            msg += "Memory allocation failed. Could not create Item: " + errVar;
            break;

        case NEW_MONSTER_FAIL:
            msg += "Memory allocation failed. Could not create Monster: " + errVar;
            break;

        case PLAYER_CREATE_FAIL:
            msg += "Failed to create Character: " + errVar + ". (Check memory or valid class type)";
            break;

        case INVALID_CREATE_ARG:
            msg += "Invalid type for creation: " + errVar + ". (Expected Room, Warrior, Thief, or Mage)";
            break;

        case INVALID_DIR_ARG:
            msg += "Invalid direction: " + errVar + ". (Expected North, South, East, or West)";
            break;

        case INVALID_ITEM_TYPE:
            msg += "Unknown Item type: " + errVar + ".";
            break;

        case ITEM_ALREADY_IN_ROOM:
            msg += "Room already contains an item. Cannot place: " + errVar;
            break;

        case PLACE_ITEM_FAIL:
            msg += "Failed to place item '" + errVar + "' (Logic or State error).";
            break;

        default:
            msg += "Unknown error occurred involving: " + errVar;
            break;
    }

    // 1. Push to the log so it appears in "output.txt"
    actionLog.push_back(msg);

    // 2. Printing to console immediately for easier debugging while running
    std::cerr << msg << std::endl; 
}

#pragma endregion

#pragma region public methods

void Game::loadFromFile(const string& filename)
{
    ifstream file(filename);
    if(!file.is_open())
    {
        cerr << "Error: Could not open file "<<filename<<endl;
        return;
    }
    string line;
    while(getline(file,line))
    {
        parseLine(line);
    }
    file.close();
}


void Game::executeCommands()
{
    for(const auto& line : pendingCommands)
    {
        stringstream ss(line);
        string command;
        ss >> command;
        if(command == "Enter") {
            currentRoom = dungeon.getStartRoom();
            if (currentRoom) 
                actionLog.push_back(player->getName() + " enters the dungeon.");
            else 
                actionLog.push_back("Error: Start room not defined.");
        }else if(command == "Move") {
            string name , dir;
            ss >> name >> dir;
            handleMove(dir);
        }else if(command == "Fight") {
            string name, monsterName;
            ss >> name >> monsterName;
            handleFight(monsterName);
        }else if (command == "PickUp") {
            string name ,itemName;
            ss >> name >>itemName;
            handlePickUp(itemName);
        }else {
            actionLog.push_back("Error: " +command + " Is not a known command! ");
        }
    }
}


void Game::outputFinalState(const string& filename)
{
    ofstream outfile(filename);
    if(!outfile.is_open()) return;

    for(const auto& line : actionLog) 
        outfile << line << endl;
    
    outfile<<endl;
    //printing final stats: 
    outfile << player->getName() <<"'s Final Stats: " <<endl;
    outfile << player->printPlayerStats() << endl;
    outfile << player->printInventory() << endl;

    outfile.close();
}
#pragma endregion