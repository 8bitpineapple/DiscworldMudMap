#ifndef GeoMap_MAP_HEADER
#define GeoMap_MAP_HEADER
#include <string>
#include "vector2.h"
#include <iostream>


//A GeoMap only contains simple information about the map image file.
//More complex information, e.g. The position of room ids on the map , are found in the minimap class.
//Each GeoMap also has a position, so that each map can be moved independantly if you want.
class GeoMap{
private:
    int id;
    std::string filename;
    std::string name;
    std::string shortName;
    Vector2 tileSize;
    Vector2 center;
    //Vector2 playerPos; //Used for highlight
    Vector2 mapPos;    //Used for panning
    int backgroundColour;
    friend class MiniMap;
    friend class SdlMiniMap;
public:
    GeoMap(int _id, std::string _filename ,std::string _name ,Vector2 _tileSize ,Vector2 _center,std::string _shortName,int _backgroundColour);
    //void SetPlayerPos(Vector2 pos);
    //Vector2 GetPlayerPos(Vector2 pos);
    void SetMapPos(Vector2 pos);
    Vector2 GetMapPos(Vector2 pos);
    //cout for debugging and whatnot
    void CoutInfo();
};
#endif
