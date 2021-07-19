#include "discworldminimap.h"

SDL_Surface* DiscworldMinimap::terrains = nullptr;

DiscworldMinimap::DiscworldMinimap(SDL_Renderer* _renderer, SDL_Window* _window): SdlMiniMap(_renderer,_window)
{
    journeyMode = false;
    if(terrains == nullptr)
    {
        terrains = IMG_Load("./maps/terrains.png");
    }
}

std::string DiscworldMinimap::TerrainsInput(std::string input)
{
    std::string output;
    if(journeyMode)
        output = "journey ";
    else
        output = "walk ";
    output.append(input);
    return output;
}
std::string DiscworldMinimap::GetExitID(std::string roomId, std::string input)
{
    std::string output = SdlMiniMap::GetExitID(roomId,input);
    if(output.size() <1)
    {
        //std::cout<<"Trying "<< TerrainsInput(input);
        output = SdlMiniMap::GetExitID(roomId,TerrainsInput(input));
    }
    return output;
}

void DiscworldMinimap::SetOuterRoom(std::string roomId, std::string outerRoomId, std::string input)
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
        Vector2 offset = InputGuess(outerRoomId, input);
        room->outerXPos  = offset.x;
        room->outerYPos = offset.y;
        room->outerRoomMapId = outerRoom->mapId;
    }
    
    return;
}

Vector2 DiscworldMinimap::JourneyGuess(std::string roomId, std::string input)
{

    //Jorney machanic details.
    //When you Journey you move 5 (?) rooms
    //Journeying will follow roads if your on one.
    //When you Jouney on a road you will stop early on intersections.
    //You can't Journey in some places (?) like mountians (?)
    Vector2 output(0,0);
    RoomData* room = GetRoom(roomId);
    if(room->mapId == 99)
    {
        output = JourneyGuess(room->xpos, room->ypos, input);
    }
    return output;
}

Vector2 DiscworldMinimap::JourneyGuess(int x, int y,std::string input)
{
    Vector2 direction = JourneyDirection(input);    
    Vector2 current(x,y);
    Vector2 next = current + direction;

    if(IsRoad(x,y))
    {
        return FollowRoad(current, next, kJourneySteps);
    }
    else
    {
        return current + direction * 6;
    }
}

Vector2 DiscworldMinimap::JourneyDirection(std::string input)
{
    Vector2 direction;
    direction.x = 0;
    direction.y = 0;
    std::string pInput = ProcessInput(input);
    //This could be a map, not sure it matters much with less than 10 options though.
    if (pInput.compare("journey n") == 0)
    {
        direction.x = 0;
        direction.y = -1;
    }
    else if (pInput.compare("journey e") == 0)
    {
        direction.x = 1;
        direction.y = 0;
    }
    else if (pInput.compare("journey s") == 0)
    {
        direction.x = 0;
        direction.y = 1;
    }
    else if (pInput.compare("journey w") == 0)
    {
        direction.x = -1;
        direction.y = 0;
    }
    else if (pInput.compare("journey ne") == 0)
    {
        direction.x = 1;
        direction.y = -1;
    }
    else if (pInput.compare("journey se") == 0)
    {
        direction.x = 1;
        direction.y = 1;
    }
    else if (pInput.compare("journey sw") == 0)
    {
        direction.x = -1;
        direction.y = 1;
    }
    else if (pInput.compare("journey nw") == 0)
    {
        direction.x = -1;
        direction.y = -1;
    }
    return direction;
}

Vector2 DiscworldMinimap::FollowRoad(Vector2 previous, Vector2 current, int steps)
{
    //std::cout << "Following : " << current.x << ", " << current.y << "\n Steps : " << steps << " Prev was " << previous.x << " , " << previous.y << std::endl;

    if(steps <= 0)
        return current;
    //Check pixel colours around current EXCEPT previous
    //If the number of roads is >1 return current  -- We're at an intersection
    //If the number of roads is == 0, return current -- We're at a dead end
    //if the number of roads is == 1 , FollowRoad(current, theRoad, steps-1)

    //My Alorithm to do this
    //Loop through rooms around current (ignoring previous)
    //Use bool roadFound to track when we find a road
    //If we find a road when roadFound is  already true, return current, We're at an intersection
    //Otherwise set roadFound = true and 
    //Set roadX and roadY to the first road found
    //If not roadFound after checking all positions, return current -- We're at a dead end
    //Only way to reach end of the code is to have found exactly 1 road
    // FollowRoad(current, roadPos, steps - 1)

    bool roadFound = false;
    Vector2 roadPos;
    roadPos.x = 0;
    roadPos.y = 0;
    

    for(int i = -1; i < 2; i++)
    {
        for(int j = -1; j < 2; j++)
        {
            if( (i == 0 && j == 0) || (previous.x == (current.x + i) && previous.y == (current.y + j) ) )
                continue; //Ignore previous and current pos
            else
            {
                
                if(IsRoad(current.x + i, current.y + j))
                {
                    if(roadFound)
                    {
                        //We found a road before, we're at an intersection.
                        return current;
                    }
                    else
                    {
                        roadFound = true;
                        roadPos.x = current.x + i;
                        roadPos.y = current.y + j;
                    }
                }
            }
        }
    }
    //We checked all positions
    if(not roadFound)
    {
        //We're at a dead end.
        return current;
    }
    else
    {
        return FollowRoad(current, roadPos, steps - 1);
    }
}

bool DiscworldMinimap::IsRoad(int x, int y)
{
    const Uint8 kRoadR = 115;
    const Uint8 kRoadG = 66;
    const Uint8 kRoadB = 24;
    SDL_Color pixColour;
    pixColour = GetTerrainsPixelColour(x,y);
    return pixColour.r == kRoadR && pixColour.g == kRoadG && pixColour.b == kRoadB;
}


Vector2 DiscworldMinimap::InputGuess(std::string roomId, std::string input)
{
    Vector2 output;
    std::string pInput = ProcessInput(input);
    if(pInput.rfind("journey",0) == 0)
        output = JourneyGuess(roomId,input);
    else
    {
        auto roomData = GetRoom(roomId);
        output.x = roomData->xpos;
        output.y = roomData->ypos;
        Vector2 tilesize = geoMapsById.find(roomData->mapId)->second->tileSize;
        Vector2 InputVector = InputToVector(input);
        Vector2 offset(InputVector.x * tilesize.x, InputVector.y * tilesize.y);
        output = output + offset;
    }
    return output;
}


//Gets colour of the terrains at x,y
SDL_Color DiscworldMinimap::GetTerrainsPixelColour(int x, int y)
{
    SDL_Color colour;
    colour.a = 255;
    colour.r = 0;
    colour.g = 0;
    colour.b = 0;
    Uint32 pixelData = GetTerrainsPixelData(x,y);
    SDL_GetRGB(pixelData,terrains->format,&colour.r,&colour.g,&colour.b);
    return colour;
}

//Adapted from https://stackoverflow.com/questions/53033971/how-to-get-the-color-of-a-specific-pixel-from-sdl-surface
Uint32 DiscworldMinimap::GetTerrainsPixelData(int x, int y)
{
    int bpp = terrains->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)terrains->pixels + y * terrains->pitch + x * bpp;
    switch (bpp)
    {
    case 1:
        return *p;
        break;

    case 2:
        return *(Uint16 *)p;
        break;

    case 3:
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;
            break;

        case 4:
            return *(Uint32 *)p;
            break;

        default:
            return 0;       /* shouldn't happen, but avoids warnings */
      }
}