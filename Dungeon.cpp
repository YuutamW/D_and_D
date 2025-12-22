// Dor Mandel :       ID: 315313825
// Yotam Weintraub:   ID: 321610859

#include "Dungeon.hpp"

#pragma region private methods

    void Dungeon::DestroyList() 
    {
        if(!head) return;
        Room* curr = head;
        while(head)
        {
            head = head->getNext();
            delete curr;
            curr = head;
        }
        head = tail = nullptr;
    }

#pragma endregion

#pragma region cnstrctrs/dstrctrs

    Dungeon::~Dungeon() {DestroyList();}
    #pragma endregion
    
    #pragma region public methods
    
    void Dungeon::addRoom(Room *roomToAdd)  {
        Dstate = Success;
        if(!roomToAdd ) {Dstate = Fail; return;}
        
        if(!head)
        {
            head = roomToAdd;
            tail = roomToAdd;
            return;
        }
        
        else 
        {
            tail->setNext(roomToAdd);//tail.next = roomToAdd
            tail = roomToAdd;   //tail = roomToAdd
            
        }
    }
    
    void Dungeon::setStartRoom(Room *roomToSet)
    {
        if(!roomToSet) 
        {
            Dstate = Fail; 
            return;
        }
        startRoom = findRoom(roomToSet->getName());
        if(!startRoom) {
            Dstate = Fail; 
            return;
        }
        Dstate = Success;
    }
    
    void Dungeon::attemptConnection(Room *roomA, Room *roomB, std::string dir)
    {
        Dstate = (roomA && roomB) ? Success : Fail;
        if(Dstate == Fail) return;
        using namespace std;
        if(dir == "East"){
            if(!roomA->getEast() && !roomB->getWest()){
                roomA->connectEast(roomB);
                roomB->connectWest(roomA);
            }
            else Dstate = Fail;
        }else if(dir =="North"){
            if(!roomA->getNorth() && !roomB->getSouth()){
                roomA->connectNorth(roomB);
                roomB->connectSouth(roomA);
            }else Dstate = Fail;
        }else if(dir == "West") {
            if(!roomA->getWest() && !roomB->getEast()){
                roomA->connectWest(roomB);
                roomB->connectEast(roomA);
            }else Dstate = Fail;
        }else if(dir == "South"){
            if(!roomA->getSouth() && !roomB->getNorth()) {
            roomA->connectSouth(roomB);
            roomB->connectNorth(roomA);
            }else Dstate = Fail;
        }
        else Dstate = Fail; 
        return;
    }

    
    Room *Dungeon::findRoom(std::string RoomName) 
    {   Dstate = Success;
        if(!head) { return nullptr; }
        Room* curr = head;
        while (curr)
        {
            if((*curr) == RoomName.c_str())
            return curr;
            curr = curr->getNext();
        }
        Dstate = Fail;
        return nullptr;
    }
    
    
    void Dungeon::placeItem(std::string roomName, Item *itemToAdd)
    {
        
        if(!itemToAdd) {
            Dstate = Fail; 
            return;
        }
        Room* roomToAddTo = findRoom(roomName);
        if(!roomToAddTo){
            Dstate = Fail; 
            return;
        }
        const Item* existingItem = roomToAddTo->getItem();
        if(existingItem && *roomToAddTo == itemToAdd)
        {
            Dstate = Fail; 
            return;
        }
        *roomToAddTo += itemToAdd;
        Dstate = Success;
        return;
    }

    void Dungeon::placeMonster(std::string roomName, Monster *mnstToAdd)
    {
        if(!mnstToAdd){
            Dstate = Fail; 
            return;
        }
        Room* roomToAddTo = findRoom(roomName);
        if(!roomToAddTo){
            Dstate = Fail; 
            return;
        }
        const Monster* existingMnstr = roomToAddTo->getMnstr();
        if(existingMnstr && *(roomToAddTo)->getMnstr() == *mnstToAdd)
        {
            Dstate = Fail; 
            return;
        }
        *roomToAddTo += mnstToAdd;
        Dstate = Success;
        return;
    }

#pragma endregion
    