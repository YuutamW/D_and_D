// Dor Mandel :       ID: 315313825
// Yotam Weintraub:   ID: 321610859

#include "Room.hpp"

#pragma region private funcs
    
    void Room::destroyRoom()
    {
        if(roomName) free(roomName);
        roomName = nullptr;
        cleanMembersInRoom();
    }

    //definition operator Ovrld. -deepCopies 
    Room &Room::operator=(const Room &other)
    {
        if(this == &other) return *this;  
        destroyRoom();
        this->roomName = (other.roomName) ? strdup(other.roomName) : nullptr;
        this->item = (other.item) ? other.item->clone() : nullptr;
        this->monster = (other.monster) ? new Monster(*other.monster) : nullptr;

        return *this;
    }
    
   

#pragma endregion

#pragma region public funcs
    
    #pragma region cnstrctrs/dstrctrs
    
    Room::Room(const Room& other) //cpy cnstrctr
    : north(nullptr), south(nullptr), east(nullptr), west(nullptr), item(nullptr) , monster(nullptr)
    {
        *this = other;
    }


    Room::~Room()
    {
        destroyRoom();
        
    }

    
    #pragma endregion
    std::string Room::printRoom() const
    {
        using namespace std;
        return "Room: " + getName() + "\n\tMonster: " + monster->printMonster() + "\n\tItem: " + item->printItem();
    }

    
#pragma endregion