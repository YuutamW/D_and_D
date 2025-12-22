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
     east(nullptr), west(nullptr), item(nullptr), monster(nullptr),next(nullptr) {}
    
     Room(const char *giveName) : roomName(strdup(giveName)), north(nullptr),
     south(nullptr),east(nullptr), west(nullptr), item(nullptr), monster(nullptr),next(nullptr) {}
    
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
    inline std::string getName() const { return roomName; }
    inline  Room* getNorth() const { return north; }
    inline  Room* getSouth() const { return south; }
    inline  Room* getEast() const { return east; }
    inline  Room* getWest() const { return west; }
    inline  Item* getItem() const { return item; }
    inline  Monster* getMnstr() const { return (monster)? monster : nullptr;}
    inline Room* getNext() const {return next;}
    std::string printRoom() const;
    inline void setNext(Room* NextRoom) {next = NextRoom;}
    
    
    //OP==: (Room_OBJ)==(const char*): if other room has no name(null) will return false regardless.
    inline bool operator==(const char* otherRoomName) const {return (otherRoomName && this->roomName) ? (strcmp(otherRoomName,this->roomName) == 0) : false ;}
    //OP==: (Room_OBJ)==(Room_OBJ):binary oprtr between two objects will check duplicates between Names
    inline bool operator==(const Room& other) const {return (other.roomName)? (*this == other.roomName ): false;}
    //OP==: (Room_OBJ)==(*ITEM_OBJ) will check to see if there is an item already in the room and if so, are the items similiar
    inline bool operator==(const Item* otherItem) const {return (item) ? *item == *otherItem : false;}
    //OP+=: (Room_OBJ)+=(*Room_OBJ) Updates the *next field 
    inline void operator+=(Room* nextRoom) { setNext(nextRoom);}
    //OP++: this = this->next
    inline Room* operator++() {return next;}
    //OP+=: (ROOM_OBJ)+=(*Item_OBJ) if there is already an item, deletes it. sets the item pointer to be the given parameter
    inline void operator+=(Item* itemToAdd) {
        if(!itemToAdd) return;
        else if(!(*this == itemToAdd)){cleanItemInRoom();item = itemToAdd;}
    }
    //OP+=: (Room_OBJ)+=(*Monster_OBJ) if there is already a monster, deletes it. sets the monster pointer to the given param
    inline void operator+=(Monster* monsterToAdd) {
        if(!monsterToAdd) return;
        if(!monster) monster = monsterToAdd;
        else if(!(*monsterToAdd == *monster)){cleanMnstrInRoom();monster = monsterToAdd;}
    }


};