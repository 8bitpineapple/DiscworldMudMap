#ifndef DISCWORLD_MAP_GENERATOR
#define DISCWORLD_MAP_GENERATOR
#include "minimap.h"
#include <sqlite3.h>
#include "roomdata.h"
#include <map>
#include <sstream>
#include <vector>
#include <list>
//sstream is used as a hack for loading ints from strings when doing SQL lookups
//***Must*** be the wrong way to do it. They'll be a way to get the int directly instead of
//retrieving it as a char* , putting it in an ssteam, and finally sticking it in the variable.

//Functions to generate a Discworld Minimap
namespace DiscworldFunctions
{
    void loadDiscworldInto(MiniMap& mmap);

    //Loads map information from cpp - May change to make it possible to add maps without rebuilding
    void addDiscworldMaps(MiniMap& mmap);
    void addDiscworldSpecialRooms(MiniMap& mmap);

    //Added as a temporary means of accessing the Discworld Object inside quowRoomCallback functions
    static MiniMap* discworldPntr;

    //Loads rooms from ./quow/_quowmap_database.db
    int addDiscworldRooms(MiniMap* mmap);
    int addDiscworldExits(MiniMap* mmap);
    void addDiscworldAliases(MiniMap* mmap);
    

    //Callback function used to load rooms using sqlite
    //Load rooms into DiscworldFunctions::discworldPntr  // YOU MUST SET IT FIRST WITH INIT
    static int quowRoomCallback(void *data, int argc, char **argv, char **azColName);

    static int quowExitsCallback(void *data, int argc, char **argv, char **azColName);

    //Tries to setup the outerrooms for all of the rooms on the Discworld.
    //An outerroom specifies the position of a room from the outside
    //E.g. The outerroom of the Drum Should be the room on filigree street outside the drum
    //The outerroom of the room on filigree street should be Sto Plains
    //The outer room of the room in Sto Plains should be the terrains
    //And then finally rooms in the terrains should have outer rooms of nullptr since they
    //Are the most zoomed out maps.
    void setupOuterRooms(MiniMap* mmap);
    static int initTerrainsIds();
    static std::vector<std::string> terrainIds;
    static int findTerrainsCallback(void *data, int argc, char **argv, char **azColName);

}
#endif