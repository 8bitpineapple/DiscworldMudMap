#include "minimap.h"
//*******************************************
//*****************Setters*******************

void MiniMap::SetCurrentMap(int id)
{
    //std::cout<<"Setting current map to ID " << id << std::endl;
    if(geoMapsById[id] != 0)
        currMap = geoMapsById[id];
    else
        std::cout<<"There is no map with id"<<id<<std::endl;
    //std::cout<<"Current map is now" << currMap << std::endl;
}

void MiniMap::SetCurrentMap(GeoMap* gMap)
{
    currMap = gMap;
}

void MiniMap::SetCurrRoomId(std::string id)
{
    currRoomId = id;
}

void MiniMap::AddGeoMap(int id,GeoMap* gMap)
 {
     geoMapsById.insert(std::pair<int,GeoMap*>(id,gMap));
     return;
 }

 void MiniMap::AddRoom(std::string id,RoomData* RoomDataPnt)
 {
     //If we've not added it before. Add it
     if(roomLookup.find(id) == roomLookup.end())
        roomLookup.insert(std::pair<std::string, RoomData*>(id,RoomDataPnt));
    return;
 }


void MiniMap::AddGeoMap(int _id, std::string _filename ,std::string _name ,Vector2 _gridSize ,Vector2 _center,std::string _shortName,int _backgroundColour)
{
    if(geoMapsById.find(_id) != geoMapsById.end() )
        return; //Already have this GeoMap loaded
    AddGeoMap(_id, new GeoMap(_id, _filename, _name, _gridSize, _center, _shortName, _backgroundColour));
}

void MiniMap::AddExit(std::string sourceId, std::string destinationId, std::string usrInput)
{
    RoomData* sourceRoom;
    if(roomLookup.find(sourceId) == roomLookup.end())
    {
        //Trying to add exits to unloaded room
        std::cout << "WARNING -- Room " << sourceId << "Isn't loaded."<<std::endl;
        throw "Cannot add exits to unloaded room";
    }
    else
    {
        sourceRoom = roomLookup.find(sourceId)->second;
        if(sourceRoom->numExits >= kMaxExits)
        {
            std::cout << "WARNING -- Room " << sourceId << "contains too many exits"<<std::endl;
            throw "Room exits exceeds max exits";
        }
        else
        {
            //Room seems loaded and has room to fit more exits
            sourceRoom->exits[sourceRoom->numExits].roomId = destinationId;
            sourceRoom->exits[sourceRoom->numExits].usrInput = usrInput;
            sourceRoom->numExits = sourceRoom->numExits + 1;

            // std::cout << sourceId << " now has " << sourceRoom->numExits << "exits" << std::endl;
            // std::cout << "This includes " << sourceRoom->exits[sourceRoom->numExits-1].usrInput << " to go to " << sourceRoom->exits[sourceRoom->numExits-1].roomId << std::endl;
        }
        
    }
    
    return;

}

//Adds an alias for a direction. E.g. north means n.
void MiniMap::AddAlias(std::string key, std::string value)
{
    aliases[key] = value;
}

void MiniMap::GuessRoom(std::string input)
{
    std::string tempRoomId = GetExitID(currRoomId,input);
    if(tempRoomId.size()>=1)
    {
        currRoomId = tempRoomId;
        return;
    }
    //Didn't find an exit with that input, maybe they gave a room id
    if(roomLookup.find(input) != roomLookup.end())
    {
        currRoomId = input;
    }

    if(input.compare("zoomout") == 0)
    {
        RoomData* currRoom = GetCurrentRoom();
        if(!currRoom->outerRoom.empty())
            currRoomId = currRoom->outerRoom;
    }
    return;
}

//Tries to convert a command, e.g. north, into a vector direction e.g. e -> (1,0), n -> (0,-1),  ne -> (1, -1) ,  sw -> (-1, 1)
Vector2 MiniMap::InputToVector(std::string input)
{
    //Tested with n,e,s,w,ne,se,sw,nw commands
    Vector2 output;
    std::string pInput = ProcessInput(input);
    
    output.x = 0;
    output.y = 0;
    //Check if it looks like a north command
    if(pInput.compare("n") == 0 || 
       pInput.compare("journey n") == 0 || 
       pInput.compare("walk n") == 0 || 
       pInput.compare("swim n") == 0 || 
       pInput.compare("north") == 0)
    {
        output.x = 0;
        output.y = -1;
    }
    else if(pInput.compare("e") == 0 || 
       pInput.compare("journey e") == 0 || 
       pInput.compare("walk e") == 0 || 
       pInput.compare("swim e") == 0 || 
       pInput.compare("east") == 0)
    {
        output.x = 1;
        output.y = 0;
    }
    else if(pInput.compare("s") == 0 || 
       pInput.compare("journey s") == 0 || 
       pInput.compare("walk s") == 0 || 
       pInput.compare("swim s") == 0 || 
       pInput.compare("south") == 0)
    {
        output.x = 0;
        output.y = 1;
    }
    else if(pInput.compare("w") == 0 || 
       pInput.compare("journey w") == 0 || 
       pInput.compare("walk w") == 0 || 
       pInput.compare("swim w") == 0 || 
       pInput.compare("west") == 0)
    {
        output.x = -1;
        output.y = 0;
    }
    else if(pInput.compare("ne") == 0 || 
       pInput.compare("journey ne") == 0 || 
       pInput.compare("walk ne") == 0 || 
       pInput.compare("swim ne") == 0 || 
       pInput.compare("northeast") == 0)
    {
        output.x = 1;
        output.y = -1;
    }
    else if(pInput.compare("se") == 0 || 
       pInput.compare("journey se") == 0 || 
       pInput.compare("walk se") == 0 || 
       pInput.compare("swim se") == 0 || 
       pInput.compare("southeast") == 0)
    {
        output.x = 1;
        output.y = 1;
    }
    else if(pInput.compare("sw") == 0 || 
       pInput.compare("journey sw") == 0 || 
       pInput.compare("walk sw") == 0 || 
       pInput.compare("swim sw") == 0 || 
       pInput.compare("southwest") == 0)
    {
        output.x = -1;
        output.y = 1;
    }
    else if(pInput.compare("nw") == 0 || 
       pInput.compare("journey nw") == 0 || 
       pInput.compare("walk nw") == 0 || 
       pInput.compare("swim nw") == 0 || 
       pInput.compare("northwest") == 0)
    {
        output.x = -1;
        output.y = -1;
    }
    return output;
}

std::string MiniMap::ProcessInput(std::string input)
{
    std::string pInput;
        if(aliases.find(input) != aliases.end())
            pInput = aliases[input];
        else
            pInput = input;
    return pInput;
}

void MiniMap::SetOuterRoom(std::string roomId, std::string outerRoomId, std::string input)
{
    RoomData* room = GetRoom(roomId);
    RoomData* outerRoom = GetRoom(outerRoomId);
    //When the rooms are on the same map we just keep the offset the same
    //and assign it the same outer room
    if(room->mapId == outerRoom->mapId)
    {
        room->outerRoom = outerRoom->outerRoom;
        room->outerXPos = outerRoom->outerXPos;
        room->outerYPos = outerRoom->outerYPos;
        room->outerRoomMapId = outerRoom->outerRoomMapId;
    }
    else
    {
        //The mapids are different set the rooms outerroom to outerroom and calc offsets
        room->outerRoom = outerRoomId;
        Vector2 offset = InputToVector(input);
        Vector2 roomTileSize = geoMapsById.find(outerRoom->mapId)->second->tileSize;
        offset.x = offset.x * roomTileSize.x;
        offset.y = offset.y * roomTileSize.y;
        room->outerXPos  = outerRoom->xpos + offset.x;
        room->outerYPos = outerRoom->ypos + offset.y;
        room->outerRoomMapId = outerRoom->mapId;
    }
    
    return;
}


void MiniMap::SetPlayerRoomId(std::string id)
{
    playerRoomId = id;
}

//*******************************************
//*****************Getters*******************

GeoMap* MiniMap::GetCurrMapPtr()
{
    return currMap;
}

RoomData* MiniMap::GetRoom(std::string room_id)
{
    return roomLookup.find(room_id)->second;
}

RoomData* MiniMap::GetCurrentRoom()
{
    return roomLookup.find(currRoomId)->second;
}


//Tries to find rooms exit if it has one, returns "" if there's not one.
std::string MiniMap::GetExitID(std::string roomId, std::string input)
{
    RoomData *room = GetRoom(roomId);
    if (room->numExits > 0)
    {
        //process the input to correct for aliases
        std::string pInput = ProcessInput(input);
        
        for (int i = 0; i < room->numExits; i++)
        {
            if (room->exits[i].usrInput == pInput)
            {
                return room->exits[i].roomId;
            }
        }
    }

    //If we get here, a room wasn't found. Return ""
    return "";
}

std::string MiniMap::GetCurrentRoomId()
{
    return currRoomId;
}

//*******************************************
//*****************Deconstructor*************
MiniMap::~MiniMap()
{
    for(auto itor = geoMapsById.begin(); itor != geoMapsById.end(); itor++)
    {
        delete itor->second;
    }

    for(auto itor = roomLookup.begin(); itor != roomLookup.end(); itor++)
    {
        delete itor->second;
    }
    
}

