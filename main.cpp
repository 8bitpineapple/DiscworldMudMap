//Standalone Discworld Mud Map adapted from Quows Minimap plugin
#include <iostream>
#include <string>
//#include "sdlminimap.h"
#include "discworldminimap.h"
#include <map>
#include "discworldfunctions.h"

#include <sstream>
#include <thread>


void imageLoopTest(SdlMiniMap& discworld, SDL_Window* window, SDL_Surface* windowSurface)
{
    SDL_Event events;
    bool running = true;

    int x = 1;
    discworld.SetCurrentMap(x);
    discworld.Blit();
    int counter = 0;
    while (running)
    {
        while (SDL_PollEvent(&events))
        {
            if (events.type == SDL_QUIT)
                running = false;
        }
        if(counter%2000 == 1)
        {
            discworld.SetCurrentMap(x);
            SDL_FillRect(windowSurface, NULL, 0xFFFFFF);
            discworld.Blit();
            SDL_UpdateWindowSurface(window);
        }
        
        x = (x+1)%63;
        counter++;
        SDL_Delay(1);
    }


}


DiscworldMinimap* globalMapPointer;
bool windowResized = false;
//Taken from https://stackoverflow.com/questions/32294913/getting-contiunous-window-resize-event-in-sdl-2
static int resizingEventWatcher(void* data, SDL_Event* event) {
  if (event->type == SDL_WINDOWEVENT &&
      event->window.event == SDL_WINDOWEVENT_RESIZED) {
    SDL_Window* window = SDL_GetWindowFromID(event->window.windowID);
    if (window == (SDL_Window*)data) 
    {
        if(globalMapPointer!=nullptr)
        {
            auto windowSurface = SDL_GetWindowSurface(window);
            globalMapPointer->SetDisplay(windowSurface);
            SDL_FillRect(windowSurface, NULL, 0xFFFFFF);
            globalMapPointer->Blit();
            windowResized = true;
        }
      
    }
  }
  return 0;
}

void displayFromUsrInput(DiscworldMinimap &discworld, SDL_Window *window, SDL_Surface *windowSurface)
{
    SDL_Event events;
    bool running = true;
    discworld.SetCurrentMap(1);
    //discworld.CenterMap();
    discworld.Blit();
    globalMapPointer = &discworld;
    SDL_AddEventWatch(resizingEventWatcher, window);
    int counter = 0;

    //Set initial room to some place in AM
    std::string userInput = "964ea3c5f971d538232e683612cd41900c232bdd";
    while (running)
    {
        //Have to get a new surface in case size change
        auto windowSurface = SDL_GetWindowSurface(window);
        discworld.SetDisplay(windowSurface);
        SDL_FillRect(windowSurface, NULL, 0xFFFFFF);

        //discworld.BlitByRoomId(roomId);
        discworld.GuessRoom(userInput);
        std::cout << std::endl << "Currentroom: " << discworld.GetCurrentRoomId();
        std::cout << std::endl << "Outerroom:"  << discworld.GetCurrentRoom()->outerRoom << std::endl;
        std::cout << std::endl << "Outer Offset " << discworld.GetCurrentRoom()->outerXPos << ", "<< discworld.GetCurrentRoom()->outerYPos << std::endl;
        discworld.CenterPlayer();
        discworld.Blit();
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

        SDL_UpdateWindowSurface(window);

        while (SDL_PollEvent(&events))
        {
            if (events.type == SDL_QUIT)
                running = false;
        }

        //std::cout << "#discworld"<<std::endl;
        //std::getline(std::cin,userInput);
        
        
        //std::cin >> userInput;
        std::getline(std::cin,userInput);
        
        //discworld.test();
        
        if (userInput == "q")
        {
            running = false;
            break;
        }
        else if (userInput == "#discworld")
        {
            std::cout << "#discworld" << std::endl;
        }

        SDL_Delay(1);
        
    }
}


void handleUserInput(std::stringstream &userInputBuffer, bool& gettingUserInput)
{
    std::string input;
    while(gettingUserInput)
    {
        std::getline(std::cin,input);
        userInputBuffer << input << std::endl;
    }
}

void displayDiscwolrdThreaded(DiscworldMinimap &discworld, SDL_Window *window, SDL_Surface *windowSurface)
{
    // std::cout << "ROAD TEST " << std::endl;
    // std::cout << discworld.FollowRoad(Vector2(1302, 3852),Vector2(1303, 3852),11).x << std::endl;
    // std::cout << discworld.FollowRoad(Vector2(1302, 3852),Vector2(1303, 3852),11).y << std::endl;
    // std::cout << "ROAD TEST " << std::endl;
    std::stringstream userInputBuffer;
    SDL_Event events;
    bool running = true;
    discworld.SetCurrentMap(1);
    //discworld.CenterMap();
    discworld.Blit();
    globalMapPointer = &discworld;
    SDL_AddEventWatch(resizingEventWatcher, window);
    int counter = 0;

    //Set initial room to some place in AM
    std::string userInput = "964ea3c5f971d538232e683612cd41900c232bdd";
    bool gettingUserInput = true;
    std::thread userInputThread(handleUserInput, std::ref(userInputBuffer), std::ref(gettingUserInput));
    userInputThread.detach();
    while (running)
    {
        //Have to get a new surface in case size change
        auto windowSurface = SDL_GetWindowSurface(window);
        discworld.SetDisplay(windowSurface);
        SDL_FillRect(windowSurface, NULL, 0xFFFFFF);

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
        if(windowResized || userInput.length() > 0)
        {
            discworld.CenterPlayer();
            discworld.Blit();
            SDL_UpdateWindowSurface(window);
        }
        windowResized = false;


        

        while (SDL_PollEvent(&events))
        {
            if (events.type == SDL_QUIT)
                running = false;
        }

        
        userInput = "";
        //userInputBuffer.clear(); //Clear any errors cause' ... whatever.
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
            std::cout << "#discworld" << std::endl;
        }

        SDL_Delay(1);
        
    }
    //Outside of while running loop
    gettingUserInput = false;
}

int main(int argc, char* argv[])
{
    //Uint32 flags = SDL_WINDOW_RESIZABLE;
    Uint32 flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALWAYS_ON_TOP;
    auto window = SDL_CreateWindow( "Discworld MudMap", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, flags);
    auto windowSurface = SDL_GetWindowSurface( window );
    SDL_Renderer* mainRenderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    SDL_FillRect(windowSurface, NULL, 0xFFFFFF);
    SDL_UpdateWindowSurface(window);
    
    //Room id's are mostly loaded from Quows database.
    //Example search through his db, using sqlite3, SELECT * from rooms WHERE room_short like '%drum%';
    std::string theDrumId = "964ea3c5f971d538232e683612cd41900c232bdd";
    DiscworldMinimap discworld(windowSurface);
    discworld.SetCurrRoomId(theDrumId);
    DiscworldFunctions::loadDiscworldInto(discworld);
    //Load images -- loadDiscworldInto only loads Minimap data, not images for SdlMiniMap
    discworld.LoadAllImages();


    //imageLoopTest(discworld,window,windowSurface);
    //displayFromUsrInput(discworld,window,windowSurface);
    displayDiscwolrdThreaded(discworld,window,windowSurface);
    SDL_Quit();
    return 0;
}
