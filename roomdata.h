#ifndef ROOMDATA_STRUCT
#define ROOMDATA_STRUCT
#include <string>


struct Exit
{
    //Storing just the roomId and not a RoomData*
    //Makes pathfinding a little slower -- From a room we have to Hash the roomID of the exit
    //To find the next room. Consider adding a RoomData* to Exit, and then if that isn't nullptr,
    //You could follow that instead of Hashing the exit RoomID.
    std::string roomId;
    std::string usrInput;
};

//Assume each room has no more than 15 exits
//We waste a bit of memory, but also don't have to deal with dynamically allocating memory
const int kMaxExits = 15;

struct RoomData
{
    int mapId;
    int xpos;
    int ypos;
    std::string shortDes;
    std::string roomType;
    int numExits;
    Exit exits[kMaxExits];

    //An outerroom and offset describe the position of this room
    //Based on a room that's considered more "outside".
    //For example, A library room with a library map id
    //with an outerroom to just outside the library on a university map
    //The room just outside the libary could have an outer room of a town map
    //Just outside the university, which will also have an outerroom.
    //
    //Eventually you'll reach "The planet" with an outerRoom = nullptr
    // ... Unless the MUD has a SolarSystem with other planets or something ...
    std::string outerRoom = "";
    int outerRoomOffsetX = 0;
    int outerRoomOffsetY = 0;
    //The magic in the outerRoom pointer is in setting them up.
    //I have an algorithm in mind for the case of Discworld -- See Discworld Functions.
};

#endif