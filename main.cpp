//Standalone Discworld Mud Map adapted from Quows Minimap plugin
#include <iostream>
#include <string>
//#include "sdlminimap.h"
#include "discworldminimap.h"
#include <map>
#include "discworldfunctions.h"

#include <sstream>
#include <thread>

void handleUserInput(std::stringstream &userInputBuffer, bool& gettingUserInput)
{
    std::string input;
    while(gettingUserInput)
    {
        std::getline(std::cin,input);
        userInputBuffer << input << std::endl;
    }
}

void displayDiscwolrdThreaded(DiscworldMinimap &discworld, SDL_Window *window, SDL_Renderer* renderer)
{
    SDL_Event events;
    bool running = true;

    //Setup Input thread
    std::stringstream userInputBuffer;
    bool gettingUserInput = true;
    //Default location to the drum.
    std::string userInput = "964ea3c5f971d538232e683612cd41900c232bdd";
    std::thread userInputThread(handleUserInput, std::ref(userInputBuffer), std::ref(gettingUserInput));
    userInputThread.detach();

    while (running)
    {
        SDL_SetRenderDrawColor(renderer,255,255,255,0);
        SDL_RenderFillRect(renderer, NULL);
        while (SDL_PollEvent(&events))
        {
            if (events.type == SDL_QUIT)
                running = false;
        }

        if(userInput.length() > 0)
        {
            discworld.GuessRoom(userInput);
            std::cout << std::endl << "Currentroom: " << discworld.GetCurrentRoomId();
            std::cout << std::endl << "Outerroom:"  << discworld.GetCurrentRoom()->outerRoom << std::endl;
            std::cout << std::endl << "Outer Cords " << discworld.GetCurrentRoom()->outerXPos << ", "<< discworld.GetCurrentRoom()->outerYPos << std::endl;
            std::cout << std::endl << "Outer Mapid " << discworld.GetCurrentRoom()->outerRoomMapId << std::endl;
            RoomData *thisRoom = discworld.GetCurrentRoom();
            if (thisRoom != nullptr && thisRoom->numExits > 0)
            {
                std::cout << "Current exits: ";
                for (int i = 0; i < thisRoom->numExits; i++)
                {
                    std::cout << thisRoom->exits[i].usrInput;
                    if (i < thisRoom->numExits)
                        std::cout << ", ";
                }
                std::cout << std::endl;
            }
        }
        
        discworld.CenterPlayer();
        discworld.Blit();

        SDL_RenderPresent(renderer);

        //Handle User Input
        userInput = "";
        userInputBuffer.clear(); //Clear any errors cause' ... whatever.
        if(userInputBuffer.rdbuf()->in_avail() != 0)
        {
            //"New input detected";
            std::getline(userInputBuffer,userInput);
        }
        
        
        if (userInput == "q")
        {
            running = false;
            break;
        }
        else if (userInput == "#discworld")
        {
            //We need this for tintin, so that we can return to #discworld from #minimap
            std::cout << "#discworld" << std::endl;
        }

        

        //Small delay.
        SDL_Delay(1);
    }

    //Cleanup 
    gettingUserInput = false;
    IMG_Quit();
}

int main(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
	std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
	return 1;
    }

    //Uint32 flags = SDL_WINDOW_RESIZABLE;
    Uint32 flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALWAYS_ON_TOP;
    auto window = SDL_CreateWindow( "Discworld MudMap", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, flags);

    SDL_Renderer* mainRenderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    if (mainRenderer == nullptr)
    {
        std::cout << "1 SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        return 0;
    }

    auto windowSurface = SDL_GetWindowSurface( window );

    
    
    SDL_FillRect(windowSurface, NULL, 0xFFFFFF);
    SDL_UpdateWindowSurface(window);
    
    //Room id's are mostly loaded from Quows database.
    //Example search through his db, using sqlite3, SELECT * from rooms WHERE room_short like '%drum%';
    std::string theDrumId = "964ea3c5f971d538232e683612cd41900c232bdd";
    DiscworldMinimap discworld(mainRenderer,window);
    discworld.SetCurrRoomId(theDrumId);
    DiscworldFunctions::loadDiscworldInto(discworld);
    //Load images -- loadDiscworldInto only loads Minimap data, not images for SdlMiniMap
    discworld.LoadAllImages();


    displayDiscwolrdThreaded(discworld,window,mainRenderer);
    SDL_Quit();
    return 0;
}
