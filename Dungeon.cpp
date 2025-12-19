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
            delete head;
            curr = head;
        }
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
    void Dungeon::connectRooms(Room* roomA, Room* roomB, std::string dir)
    {
        Dstate = (roomA && roomB) ? Success : Fail;
        if(Dstate == Fail) return;
        using namespace std;
        if(dir == "East"){
            roomA->connectEast(roomB);
            roomB->connectWest(roomA);
        }else if(dir =="North"){
            roomA->connectNorth(roomB);
            roomB->connectSouth(roomA);
        }else if(dir == "West") {
            roomA->connectWest(roomB);
            roomB->connectEast(roomA);
        }else if(dir == "South"){
            roomA->connectSouth(roomB);
            roomB->connectNorth(roomA);
        }
        else Dstate = Fail;
        
        return;
 
    }

    Room *Dungeon::findRoom(std::string RoomName) const
    {
        if(!head) { return nullptr; }
        Room* curr = head;
        while (curr)
        {
            if((*curr) == RoomName.c_str())
            return curr;
        }
        return nullptr;
    }

#pragma endregion
