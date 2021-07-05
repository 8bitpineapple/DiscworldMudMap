#ifndef SDL_MINIMAP_HEADER
#define SDL_MINIMAP_HEADER

#include "minimap.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>
#include <string>
#include <iostream> //For Debbing

//Marker struct contains data for drawing on a map.
struct marker
{
	int x = 0;
	int y = 0;
	int h = 25;
	int w = 25;
	int mapId = 0;
	Uint32 colour = 0x000000;
//Room Id may be used for getting extra information about the marker.
//And initialising x,y,h,w,
//NOTE somtimes we might mark coordinates we don't know the roomId
	std::string roomId = "";
};

//A minimap with SDL functions for displaying it and loading Geomaps.
class SdlMiniMap : public MiniMap
{
private:
    SDL_Surface* currentMapArt;
    RoomData* currentRoom;

    SDL_Surface* display;
    SDL_Window* window;
    bool AddImage(int id,std::string imageDir);
    SDL_Surface* updateCurrentMapArt();
    Vector2 artDestination;
    Vector2 artSize;
    Vector2 playerDestination;  // Position of player highlight
    Vector2 playerSize;

    //Maps ID's to Loaded Image Surfaces
    std::map<int,SDL_Surface*> imageById;
    //std::map<int,SDL_Texture*> textureById;
public:
    SdlMiniMap(SDL_Surface* _display);
    ~SdlMiniMap();

    void DrawMarker(marker& mark);
    marker MakeMarker(int x,int y);

    void Blit();
    void LoadAllImages();
    void SetDisplay(SDL_Surface* _display);

    SDL_Surface* GetCurrentMapArt();
    void CenterPlayer();

};


// class MiniMap{
// private:
//     GeoMap* currMap;
//     GeoMap* prevMap;
// protected:
//     std::string currRoomId;
//     std::string prevRoomId;
//     std::map<int,GeoMap*> geoMapsById;
//     std::map<std::string,RoomData*> roomLookup;
// public:
//     MiniMap(){};
//     ~MiniMap();
//     void AddGeoMap(int id,GeoMap* gMap);
//     void AddGeoMap(int _id, std::string _filename ,std::string _name ,Vector2 _gridSize ,Vector2 _center,std::string _shortName,int _backgroundColour);
//     void AddRoom(std::string id,RoomData* RoomDataPnt);
//     void AddExit(std::string sourceId, std::string destinationId, std::string usrInput);
//     RoomData* GetRoom(std::string room_id);
//     RoomData* GetCurrentRoom();

//     void SetCurrentMap(int id);
//     void SetCurrentMap(GeoMap* gMap);
//     void SetCurrRoomId(std::string id);

//     void GuessRoom(std::string input);


//     GeoMap* GetCurrMapPtr();
// };


#endif