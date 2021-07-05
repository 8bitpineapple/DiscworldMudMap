#ifndef DISCWORLD_MINIMAP_HEADER
#define DISCWORLD_MINIMAP_HEADER
#include "sdlminimap.h"
#include <string>

class DiscworldMinimap : public SdlMiniMap
{
public:
    DiscworldMinimap(SDL_Surface* _display) : SdlMiniMap(_display) {journeyMode = false;}
    //Appends journey or walk onto input depending on journeyMode
    std::string TerrainsInput(std::string input);
    std::string GetExitID(std::string roomId, std::string input) override;

private:
    //In Discworld you can Journey or Walk in the terrains.
    //There's an option which you want to default to when just saying "east" for example. 
    bool journeyMode;
    
};
#endif