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
    SDL_Texture* currentMapArt;
    RoomData* currentRoom;

    SDL_Surface* display;
    SDL_Window* window;
    bool AddImage(int id,std::string imageDir);
    SDL_Surface* updateCurrentMapArt();
    Vector2 artDestination;
    Vector2 artSize;
    Vector2 playerDestination;  // Position of player highlight
    Vector2 playerSize;

    //Maps ID's to loaded Textures
    static std::map<int,SDL_Texture*> textureById;

    SDL_Renderer* renderer;
    static int SdlMiniMapCount;
    
public:
    SdlMiniMap(SDL_Renderer* _renderer, SDL_Window* _window);
    ~SdlMiniMap();

    void DrawMarker(Marker& mark);
    Marker MakeMarker(int x,int y);

    void Blit();
    void LoadAllImages();
    //void SetDisplay(SDL_Surface* _display);
    void SetRenderer(SDL_Renderer* _renderer);
    void SetWindow(SDL_Window* _window);

    SDL_Texture* GetCurrentMapArt();
    void CenterPlayer();

};

#endif