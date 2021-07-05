#include "geomap.h"

GeoMap::GeoMap(int _id, std::string _filename ,std::string _name ,Vector2 _tileSize ,Vector2 _center ,std::string _shortName,int _backgroundColour)
{
    id = _id;
    filename = _filename;
    name = _name;
    tileSize = _tileSize;
    center = _center;
    mapPos = _center;
    shortName = _shortName;
    backgroundColour = backgroundColour;
    return;
}
// void GeoMap::SetPlayerPos(Vector2 pos)
// {
//     playerPos = pos;
//     return;
// }

void GeoMap::SetMapPos(Vector2 pos)
{
    mapPos = pos;
    return;
}

// Vector2 GeoMap::GetPlayerPos(Vector2 pos)
// {
//     return playerPos;
// }

Vector2 GeoMap::GetMapPos(Vector2 pos)
{
    return mapPos;
}

void GeoMap::CoutInfo()
{
    std::cout << "id = " << id << std::endl;
    std::cout << "filename = " << filename << std::endl;
    std::cout << "name = " << name << std::endl;
    std::cout << "tileSize = " << tileSize.x << ", " << tileSize.y << std::endl;
    std::cout << "center = " << center.x << ", " << center.y << std::endl;
    std::cout << "mapPos = " << mapPos.x << ", " << mapPos.y << std::endl;
    std::cout << "shortName = " << shortName << std::endl;
}

// void GeoMap::Move(char dir)
// {
//     switch (dir)
//     {
//     case 'N':
//     case 'n':
//         /* code */
//         break;
    
//     default:
//         break;
//     }
// }