// Dor Mandel :       ID: 315313825
// Yotam Weintraub:   ID: 321610859

#include <iostream>
#include "Dungeon.hpp"
#include "Room.hpp"

Dungeon::Dungeon(int numOfRooms)
 : startRoom(nullptr)
{
   rooms = new Room*[numOfRooms];
}

Dungeon::~Dungeon()
{

}

void Dungeon::setStartRoom(Room *room)
{
    if(!room){return;}
    startRoom ;//
}

void Dungeon::addRoom(Room *room)
{

}

Room *Dungeon::findRoom(char *name)
{
    return nullptr;
}
