#include "sdlminimap.h"


std::map<int,SDL_Texture*> SdlMiniMap::textureById;

int SdlMiniMap::SdlMiniMapCount = 0;

SdlMiniMap::SdlMiniMap(SDL_Renderer* _renderer, SDL_Window* _window)
{
    SdlMiniMapCount++;
    renderer = _renderer;
    window = _window;
    artSize.y = 768;
    artSize.x = 1024;
    artDestination.x = 0;
    artDestination.y = 0;

    playerSize.y = 25;
    playerSize.x = 25;
    playerDestination.x = 0;
    playerDestination.y = 0;
}
SdlMiniMap::~SdlMiniMap()
{
    SdlMiniMapCount--;
    if(SdlMiniMapCount <= 0)
    {
        for(auto itor = textureById.begin();itor !=textureById.end(); itor++)
        {
            SDL_DestroyTexture(itor->second);
        }
    }
    
}

// void SdlMiniMap::SetDisplay(SDL_Surface* _display)
// {
//     display = _display;
// }

void SdlMiniMap::SetRenderer(SDL_Renderer* _renderer)
{
    renderer = _renderer;
}

void SdlMiniMap::SetWindow(SDL_Window* _window)
{
    window = _window;
}

bool SdlMiniMap::AddImage(int id,std::string imageDir)
{
    if(textureById.find(id) == textureById.end())
    {
        //Not loaded yet
        SDL_Surface* surfacePtr = IMG_Load(imageDir.c_str());
        //imageById.insert(std::pair<int,SDL_Surface*>(id,surfacePtr));
        SDL_Texture* texturePtr = SDL_CreateTextureFromSurface(renderer, surfacePtr);
        SDL_FreeSurface(surfacePtr);
        textureById.insert(std::pair<int,SDL_Texture*>(id,texturePtr));
        return true;
    }
    else
    {
        //Already loaded
        return true;
    }

    return false;
}


void SdlMiniMap::LoadAllImages()
{
   for(auto itor = geoMapsById.begin(); itor != geoMapsById.end(); itor++)
   {
       std::string imageDir = "./maps/";
       imageDir.append(itor->second->filename);
       AddImage(itor->first,imageDir);
   }

}


SDL_Texture* SdlMiniMap::GetCurrentMapArt()
{
    int id = GetCurrMapPtr()->id;
    //Check if art is loaded
    if(textureById.find(id) == textureById.end())
    {
        //Map isn't loaded, load it
        std::string imageDir = "./maps/";
        imageDir.append(GetCurrMapPtr()->filename);
        AddImage(id, imageDir.c_str());
    }
    //Return the Art
    return textureById.find(id)->second;

}

void SdlMiniMap::Blit()
{

    // // std::cout << "x" << artDestination.x << std::endl;
    // // std::cout << "y" << artDestination.y << std::endl;

    // SDL_Rect artDestRect;
    // artDestRect.x = artDestination.x;
    // artDestRect.y = artDestination.y;
    // artDestRect.h = artSize.y;
    // artDestRect.w = artSize.x;
    
    // SDL_Rect playerHighlightRect;

    // playerHighlightRect.x = playerDestination.x;
    // playerHighlightRect.y = playerDestination.y;
    // playerHighlightRect.h = playerSize.y;
    // playerHighlightRect.w = playerSize.x;

    // //Blit art on the screen
    // //SDL_BlitSurface(currentMapArt, NULL, display, &artDestRect);
    // SDL_RenderCopy(renderer,currentMapArt,NULL, artDestRect);

    // //Render art on screen

    // //Blit highlight onto display
    // //SDL_FillRect(display,&playerHighlightRect,0xEE0000);

    

    //Notes
    //We want to maintain the aspect ratio of the image
    //We don't want to scale the image when resizing the window (?)
    //We want to center the camera position 


    SDL_Rect artDestRect;
    artDestRect.x = artDestination.x;
    artDestRect.y = artDestination.y;
    artDestRect.h = artSize.y;
    artDestRect.w = artSize.x;
    SDL_RenderCopy(renderer,currentMapArt,NULL,&artDestRect);

    SDL_Rect playerHighlightRect;

    playerHighlightRect.x = playerDestination.x;
    playerHighlightRect.y = playerDestination.y;
    playerHighlightRect.h = playerSize.y;
    playerHighlightRect.w = playerSize.x;
    SDL_SetRenderDrawColor(renderer,255,0,0,255);
    SDL_RenderFillRect(renderer,&playerHighlightRect);

}

void SdlMiniMap::DrawMarker(Marker& mark)
{
    SDL_Rect highlight;
    //The highlight position needs to be modified by the current artDestination
    highlight.x = mark.x + artDestination.x - mark.w/3;
    highlight.y = mark.y + artDestination.y - mark.h/3;
    highlight.h = mark.h;
    highlight.w = mark.w;

    SDL_Rect highlight2;
    highlight2.x = highlight.x - 2;
    highlight2.y = highlight.y - 2;
    highlight2.h = highlight.h + 4;
    highlight2.w =  highlight.w +4;
    auto colour2 = 0x000000;

    SDL_FillRect(display,&highlight2,colour2);
    SDL_FillRect(display,&highlight,mark.colour);
    return;
}

Marker SdlMiniMap::MakeMarker(int x,int y)
{
    Marker output;
    if(roomLookup.find(currRoomId) != roomLookup.end())
    {
        GeoMap* currGeoMap = GetCurrMapPtr();
	//Set player highlight size
        output.h = (currGeoMap->tileSize.y/14)*6;
        output.w = (currGeoMap->tileSize.y/14)*6;
        output.mapId = currGeoMap->id;
    }
        //If Scaling makes it less than 3 pix, just make it 3 pix --- so it's easier to see
    if(output.h< 3)
        output.h= 3;
    if(output.w< 3)
        output.w= 3;
    
    output.x = x;
    output.y = y;
    return output;
}

void SdlMiniMap::CenterPlayer()
{
    
    //Check if current  room id location is known
    if(roomLookup.find(currRoomId) != roomLookup.end())
    {
        //Set current room
        currentRoom = roomLookup.find(currRoomId)->second;
        //Look at map the room is in
        SetCurrentMap(currentRoom->mapId);
        //Get the art for the map
        currentMapArt = GetCurrentMapArt();
        //Get extra data for map
        GeoMap* currGeoMap = GetCurrMapPtr();

        int displayW;
        int displayH;
        SDL_GetWindowSize(window,&displayW,&displayH);
        //Shift art so room pos is in the center
        artDestination.x = (displayW / 2) - currentRoom->xpos;
        artDestination.y = (displayH / 2) - currentRoom->ypos;

        SDL_QueryTexture(currentMapArt, NULL, NULL, &artSize.x, &artSize.y);

        //Set player highlight size
        playerSize.y = (currGeoMap->tileSize.y/14)*6;
        playerSize.x = (currGeoMap->tileSize.y/14)*6;

        //If Scaling makes it less than 3 pix, just make it 3 pix --- so it's easier to see
        if(playerSize.y < 3)
            playerSize.y = 3;
        if(playerSize.x < 3)
            playerSize.x = 3;

        //Put highlight in the right place
        //Since the players room is centered, highlight is in the middle.
        playerDestination.x = (displayW / 2) - playerSize.x/3;
        playerDestination.y = (displayH / 2) - playerSize.y/3;

        //std::cout << currentRoom->xpos<< ", " << currentRoom->ypos;
        
    }
    else
    {
        //We don't know where this room is, for now just display the old one
        //Later we can try to "guess" from how the player moved.
        //std::cout << "UNKNOWN ROOM ID" << std::endl;


        return;
    }
    
    return;
}



