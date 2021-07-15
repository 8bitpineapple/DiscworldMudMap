#ifndef SDL_MINIMAP_HEADER
#define SDL_MINIMAP_HEADER

#include "minimap.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>
#include <string>
#include <iostream> //For Debbing
#include "marker.h"

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
    static std::map<int,SDL_Surface*> imageById;
    static int SdlMiniMapCount;
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

#endif