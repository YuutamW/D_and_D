// Dor Mandel :       ID: 315313825
// Yotam Weintraub:   ID: 321610859

#pragma once
#include <iostream>
#include <cstring>
#include "Item.hpp"
#include "Monster.hpp"

class Room
{
private:
    char *roomName;
    Room *north, *south, *east, *west;
    Item *item;
    Monster *monster;

    Room* next;

    //private funcs
    void destroyRoom();
    Room& operator=(const Room& other);
    inline void cleanItemInRoom() {if(item) delete item; item = nullptr;}
    inline void cleanMnstrInRoom() {if(monster) delete monster;}
    inline void cleanMembersInRoom() {cleanItemInRoom(); cleanMnstrInRoom();}
public:
     Room() : roomName(nullptr), north(nullptr), south(nullptr),
     east(nullptr), west(nullptr), item(nullptr), monster(nullptr) {}
    
     Room(char *giveName) : roomName(strdup(giveName)), north(nullptr),
     south(nullptr),east(nullptr), west(nullptr), item(nullptr), monster(nullptr) {}
    
     Room(const Room& other);
    ~Room();

    //connectFuncs
    inline void connectNorth(Room *northernRoom) {this->north = northernRoom; }//northernRoom->connectSouth(this);}
    inline void connectSouth(Room *southernRoom) {this->south = southernRoom; }// southernRoom->connectNorth(this);}
    inline void connectEast(Room *easternRoom) {this->east = easternRoom; }//easternRoom->connectWest(this);}
    inline void connectWest(Room *westernRoom) {this->west = westernRoom; }//westernRoom->connectEast(this);
    inline void setItem(Item *itemToAdd) {cleanItemInRoom();  this->item = (itemToAdd) ? itemToAdd->clone() : nullptr;}
    inline void setMonster(Monster* mnstrToAdd) {cleanMnstrInRoom(); this->monster = (mnstrToAdd) ? new Monster(*mnstrToAdd) : nullptr;}

    //getters&setters
    inline const char* getName() const { return roomName; }
    inline const Room* getNorth() const { return north; }
    inline const Room* getSouth() const { return south; }
    inline const Room* getEast() const { return east; }
    inline const Room* getWest() const { return west; }
    inline const Item* getItem() const { return item; }
    inline const Monster* getMnstr() const { return monster;}
    inline Room* getNext() const {return next;}
    inline void setNext(Room* NextRoom) {next = NextRoom;}

    
    //OP: (Room_OBJ)==(const char*): if other room has no name(null) will return false regardless.
    inline bool operator==(const char* otherRoomName) const {return (otherRoomName && this->roomName) ? (strcmp(otherRoomName,this->roomName) == 0) : false ;}
    
    //OP: (Room_OBJ)==(Room_OBJ):binary oprtr between two objects will check duplicates between Names AND Monsters.
    inline bool operator==(const Room& other) const {return (other.roomName)? (*this == other.roomName && *(this)->monster == *(other).monster): false;}

};