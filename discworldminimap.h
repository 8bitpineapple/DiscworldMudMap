#ifndef DISCWORLD_MINIMAP_HEADER
#define DISCWORLD_MINIMAP_HEADER
#include "sdlminimap.h"
#include <string>
#include "vector2.h"
#include <map>

enum RoomTypeIds
{
    kUnkown,
    kRiver,
    kLake,
    kCabbage,
    kForest1,
    kForest2
};

class DiscworldMinimap : public SdlMiniMap
{
public:
    //DiscworldMinimap(SDL_Surface* _display) : SdlMiniMap(_display) {journeyMode = false;}
    DiscworldMinimap(SDL_Surface* _display);
    //Appends journey or walk onto input depending on journeyMode
    std::string TerrainsInput(std::string input);
    std::string GetExitID(std::string roomId, std::string input) override;
    //Override SetOuterRoom to account for the Journey Mechanic in offsets,
    void SetOuterRoom(std::string roomId, std::string outerRoomId, std::string input) override;
    //Tries to guess the difference in position after a journey
    Vector2 JourneyGuess(std::string roomId, std::string input);
    Vector2 JourneyGuess(int x, int y,std::string input);
    //Guess difference in position for input in a known room id.
    Vector2 InputGuess(std::string roomId, std::string input); 

    //Returns the colour of pixel x,y on terrains.png
    SDL_Color GetTerrainsPixelColour(int x, int y);
    Vector2 FollowRoad(Vector2 previous, Vector2 current, int steps);

private:
    //In Discworld you can Journey or Walk in the terrains.
    //There's an option which you want to default to when just saying "east" for example. 
    bool journeyMode;
    Vector2 terrainsPos;

    //Each pixel represents a room.
    static SDL_Surface* terrains;
    Uint32 GetTerrainsPixelData(int x, int y);

    //Recursively follows a road "steps" steps -- ends early on intersecions and end of roads.
    
    bool IsRoad(int x, int y);
    Vector2 JourneyDirection(std::string input);
    const int kJourneySteps = 11;

    
};
#endif