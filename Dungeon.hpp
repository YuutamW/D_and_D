// Dor Mandel :       ID: 315313825
// Yotam Weintraub:   ID: 321610859

#pragma once
#include "Room.hpp"
#include <iostream>

class Room; // frwdDecleration

class Dungeon
{
private:
    Room* head = nullptr , *tail = nullptr;
    Room* startRoom = nullptr ;

    void DestroyList();
    enum State
    {
        Success,
        Fail,
    };   
    
public:

    Dungeon() {}
    ~Dungeon();

    State Dstate = Success;
    //--setup methods--
    void addRoom(Room* roomToAdd);
    void setStartRoom(Room* roomToSet);
    void attemptConnection(Room* roomA, Room* roomB, std::string dir);

    //--populate methods--
    void placeItem(std::string roomName, Item* itemToAdd);
    void placeMonster(std::string roomName, Monster* mnstToAdd);

    Room* findRoom(std::string RoomName);
    inline Room* getStartRoom() const {return startRoom;}
    inline bool getState() const {return (Dstate == Success);}
};

