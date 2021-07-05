#ifndef MUD_MINIMAP_HEADER
#define MUD_MINIMAP_HEADER
#include "geomap.h"
#include <map>
#include "roomdata.h"
//Note, Try not to get confused between a "std::map" -- Mapping function
//And a "GeoMap" -- Geographical Map

#include <iostream> //Just for some debugging


//The minimap holds room data -- so we can correctly know which pixels of a geomap belong to what room
//The minimap also knows room exits for use in navigation.
//The minimap has a collection of Geomaps -- Geomaps are just for getting information about  geographical map image files.
//Used as a base class for minimaps with draw functions, i.e. SDL Minimap.
class MiniMap{
private:
    GeoMap* currMap;
    GeoMap* prevMap;
    Vector2 InputToVector(std::string input);
protected:
    std::string currRoomId;
    std::string prevRoomId;
    std::string playerRoomId;
    std::map<int,GeoMap*> geoMapsById;
    std::map<std::string,RoomData*> roomLookup;
    std::map<std::string, std::string> aliases;
public:
    MiniMap(){};
    ~MiniMap();
    void AddGeoMap(int id,GeoMap* gMap);
    void AddGeoMap(int _id, std::string _filename ,std::string _name ,Vector2 _gridSize ,Vector2 _center,std::string _shortName,int _backgroundColour);
    void AddRoom(std::string id,RoomData* RoomDataPnt);
    void AddExit(std::string sourceId, std::string destinationId, std::string usrInput);
    RoomData* GetRoom(std::string room_id);
    RoomData* GetCurrentRoom();

    void SetCurrentMap(int id);
    void SetCurrentMap(GeoMap* gMap);
    void SetCurrRoomId(std::string id);

    void SetPlayerRoomId(std::string id);

    void GuessRoom(std::string input);

    virtual std::string GetExitID(std::string roomId, std::string input);

    void AddAlias(std::string key, std::string value);

    //Sets room outer room to outerroom and tries to guess the offset based on userInput, i.e. n = 1 up i.e. y=-1
    void SetOuterRoom(std::string roomId, std::string outerRoomId, std::string input);

    GeoMap* GetCurrMapPtr();
};


#endif