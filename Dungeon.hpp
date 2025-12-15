// Dor Mandel :       ID: 315313825
// Yotam Weintraub:   ID: 321610859

#pragma once
#include "Room.hpp"
#include <iostream>

#define NUM_OF_ROOMS 10

class Room; // frwdDecleration

class Dungeon
{
private:
    Room* startRoom = nullptr ;
    Room** rooms;
public:
    Dungeon(int numOfRooms = NUM_OF_ROOMS);
    ~Dungeon();
    void setStartRoom(Room* room);
    void addRoom(Room* room);
    Room* findRoom(char* name);

};

