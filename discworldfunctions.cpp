#include "discworldfunctions.h"



void DiscworldFunctions::loadDiscworldInto(MiniMap& mmap)
{
    addDiscworldMaps(mmap);
    addDiscworldSpecialRooms(mmap);
    addDiscworldRooms(&mmap);
    addDiscworldExits(&mmap);
    addDiscworldAliases(&mmap);
    DiscworldFunctions::setupOuterRooms(&mmap);
}

void DiscworldFunctions::addDiscworldMaps(MiniMap &mmap)
{
    //I used regex in vim on Quows XML to make these contructors, e.g. :%s/[0-9]\+, [0-9]\+/Vector2(\0)/g
    //Could load from a file. But I don't think we'll get new maps often? And this is a prototype
    //Generated from Quow's Lua code. Keeping the Ids the same to use his Database
    //Note there are some gaps in ID's e.g. 36 and 64 - 98.
    mmap.AddGeoMap(1, "am.png", "Ankh-Morpork", Vector2(14, 14), Vector2(718, 802), "AM", 16777215);
    mmap.AddGeoMap(2, "am_assassins.png", "AM Assassins", Vector2(28, 28), Vector2(457, 61), "AM", 16777215);
    mmap.AddGeoMap(3, "am_buildings.png", "AM Buildings", Vector2(25, 25), Vector2(208, 76), "AM", 16777215);
    mmap.AddGeoMap(4, "am_cruets.png", "AM Cruets", Vector2(24, 24), Vector2(300, 69), "AM", 16777215);
    mmap.AddGeoMap(5, "am_docks.png", "AM Docks", Vector2(14, 14), Vector2(174, 216), "AM", 16777215);
    mmap.AddGeoMap(6, "am_guilds.png", "AM Guilds", Vector2(28, 28), Vector2(487, 245), "AM", 16777215);
    mmap.AddGeoMap(7, "am_isle_gods.png", "AM Isle of Gods", Vector2(24, 24), Vector2(342, 587), "AM", 16777215);
    mmap.AddGeoMap(8, "am_shades.png", "Shades Maze", Vector2(80, 80), Vector2(46, 179), "AM", 12895428);
    mmap.AddGeoMap(9, "am_smallgods.png", "Temple of Small Gods", Vector2(24, 24), Vector2(221, 224), "AM", 16777215);
    mmap.AddGeoMap(10, "am_temples.png", "AM Temples", Vector2(24, 24), Vector2(575, 419), "AM", 16777215);
    mmap.AddGeoMap(11, "am_thieves.png", "AM Thieves", Vector2(28, 28), Vector2(431, 300), "AM", 16777215);
    mmap.AddGeoMap(12, "am_uu.png", "Unseen University", Vector2(28, 28), Vector2(166, 393), "AM", 16777215);
    mmap.AddGeoMap(13, "am_warriors.png", "AM Warriors", Vector2(32, 25), Vector2(135, 104), "AM", 16777215);
    mmap.AddGeoMap(14, "am_watch_house.png", "Pseudopolis Watch House", Vector2(24, 24), Vector2(88, 104), "AM", 16777215);
    mmap.AddGeoMap(15, "magpyr.png", "Magpyr's Castle", Vector2(20, 20), Vector2(141, 440), "Magpyr", 16777215);
    mmap.AddGeoMap(16, "bois.png", "Bois", Vector2(14, 14), Vector2(239, 169), "Bois", 16777215);
    mmap.AddGeoMap(17, "bp.png", "Bes Pelargic", Vector2(14, 14), Vector2(1070, 748), "BP", 16777215);
    mmap.AddGeoMap(18, "bp_buildings.png", "BP Buildings", Vector2(24, 24), Vector2(428, 177), "BP", 16777215);
    mmap.AddGeoMap(19, "bp_estates.png", "BP Estates", Vector2(14, 14), Vector2(540, 506), "BP", 16777215);
    mmap.AddGeoMap(20, "bp_wizards.png", "BP Wizards", Vector2(20, 20), Vector2(101, 517), "BP", 16777215);
    mmap.AddGeoMap(21, "brown_islands.png", "Brown Islands", Vector2(28, 28), Vector2(105, 101), "Brown", 16777215);
    mmap.AddGeoMap(22, "deaths_domain.png", "Death's Domain", Vector2(28, 28), Vector2(98, 86), "Death", 16777215);
    mmap.AddGeoMap(23, "djb.png", "Djelibeybi", Vector2(14, 14), Vector2(438, 369), "DJB", 16777215);
    mmap.AddGeoMap(24, "djb_wizards.png", "IIL - DJB Wizards", Vector2(28, 28), Vector2(210, 210), "DJB", 16777215);
    mmap.AddGeoMap(25, "ephebe.png", "Ephebe", Vector2(14, 14), Vector2(407, 349), "Ephebe", 16777215);
    mmap.AddGeoMap(26, "ephebe_under.png", "Ephebe Underdocks", Vector2(14, 14), Vector2(247, 285), "Ephebe", 16777215);
    mmap.AddGeoMap(27, "genua.png", "Genua", Vector2(14, 14), Vector2(470, 242), "Genua", 16777215);
    mmap.AddGeoMap(28, "genua_sewers.png", "Genua Sewers", Vector2(21, 21), Vector2(405, 312), "Genua", 16777215);
    mmap.AddGeoMap(29, "grflx.png", "GRFLX Caves", Vector2(20, 20), Vector2(303, 222), "GRFLX", 16777215);
    mmap.AddGeoMap(30, "hashishim_caves.png", "Hashishim Caves", Vector2(28, 28), Vector2(258, 132), "Klatch", 16777215);
    mmap.AddGeoMap(31, "klatch.png", "Klatch Region", Vector2(14, 14), Vector2(724, 515), "Klatch", 16777215);
    mmap.AddGeoMap(32, "lancre_castle.png", "Lancre Region", Vector2(14, 14), Vector2(285, 33), "Ramtops", 16777215);
    mmap.AddGeoMap(33, "mano_rossa.png", "Mano Rossa", Vector2(28, 28), Vector2(298, 202), "Genua", 16777215);
    mmap.AddGeoMap(34, "monks_cool.png", "Monks of Cool", Vector2(14, 14), Vector2(113, 170), "Ramtops", 16777215);
    mmap.AddGeoMap(35, "netherworld.png", "Netherworld", Vector2(14, 14), Vector2(42, 75), "Nether", 16777215);
    mmap.AddGeoMap(37, "pumpkin_town.png", "Pumpkin Town", Vector2(48, 48), Vector2(375, 194), "Pumpkin", 16777215);
    mmap.AddGeoMap(38, "ramtops.png", "Ramtops Regions", Vector2(14, 14), Vector2(827, 223), "Ramtops", 16777215);
    mmap.AddGeoMap(39, "sl.png", "Sto-Lat", Vector2(14, 14), Vector2(367, 222), "Sto-Lat", 16777215);
    mmap.AddGeoMap(40, "sl_aoa.png", "Academy of Artificers", Vector2(25, 25), Vector2(47, 87), "Sto-Lat", 16777215);
    mmap.AddGeoMap(41, "sl_cabbages.png", "Cabbage Warehouse", Vector2(28, 28), Vector2(60, 92), "Sto-Lat", 16777215);
    mmap.AddGeoMap(42, "sl_library.png", "AoA Library", Vector2(57, 57), Vector2(220, 411), "Sto-Lat", 16777215);
    mmap.AddGeoMap(43, "sl_sewers.png", "Sto-Lat Sewers", Vector2(14, 14), Vector2(162, 204), "Sto-Lat", 16777215);
    mmap.AddGeoMap(44, "sprite_caves.png", "Sprite Caves", Vector2(14, 14), Vector2(113, 182), "Sprites", 16777215);
    mmap.AddGeoMap(45, "sto_plains.png", "Sto Plains Region", Vector2(14, 14), Vector2(752, 390), "Sto-Plains", 16777215);
    mmap.AddGeoMap(46, "uberwald.png", "Uberwald Region", Vector2(14, 14), Vector2(673, 643), "Uber", 16777215);
    mmap.AddGeoMap(47, "uu_library_full.png", "UU Library", Vector2(30, 30), Vector2(165, 4810), "UU", 16777215);
    mmap.AddGeoMap(48, "farmsteads.png", "Klatchian Farmsteads", Vector2(28, 28), Vector2(445, 171), "Klatch", 16777215);
    mmap.AddGeoMap(49, "ctf_arena.png", "CTF Arena", Vector2(48, 48), Vector2(307, 283), "CTF", 16777215);
    mmap.AddGeoMap(50, "pk_arena.png", "PK Arena", Vector2(30, 30), Vector2(155, 331), "PK", 16777215);
    mmap.AddGeoMap(51, "am_postoffice.png", "AM Post Office", Vector2(28, 28), Vector2(156, 69), "AM", 16777215);
    mmap.AddGeoMap(52, "bp_ninjas.png", "Ninja Guild", Vector2(28, 28), Vector2(109, 56), "BP", 16777215);
    mmap.AddGeoMap(53, "tshop.png", "The Travelling Shop", Vector2(28, 28), Vector2(355, 315), "T-Shop", 16777215);
    mmap.AddGeoMap(54, "slippery_hollow.png", "Slippery Hollow", Vector2(14, 14), Vector2(215, 123), "S-Hollow", 16777215);
    mmap.AddGeoMap(55, "creel_guild.png", "House of Magic - Creel", Vector2(28, 28), Vector2(38, 86), "Ramtops", 16777215);
    mmap.AddGeoMap(56, "quow_specials.png", "Special Areas", Vector2(28, 28), Vector2(288, 28), "Misc", 16777215);
    mmap.AddGeoMap(57, "skund_wolftrails.png", "Skund Wolf Trail", Vector2(12, 12), Vector2(41, 587), "Skund", 16777215);
    mmap.AddGeoMap(58, "medina.png", "Medina", Vector2(38, 38), Vector2(131, 126), "BP", 16777215);
    mmap.AddGeoMap(59, "copperhead.png", "Copperhead", Vector2(12, 12), Vector2(55, 47), "Copper", 16777215);
    mmap.AddGeoMap(60, "ephebe_citadel.png", "The Citadel", Vector2(11, 11), Vector2(37, 74), "Ephebe", 16777215);
    mmap.AddGeoMap(61, "am_fools.png", "AM Fools' Guild", Vector2(28, 28), Vector2(13, 65), "AM", 16777215);
    mmap.AddGeoMap(62, "thursday.png", "Thursday's Island", Vector2(28, 28), Vector2(112, 65), "Thursday", 16777215);
    mmap.AddGeoMap(63, "unsinkable.png", "SS Unsinkable", Vector2(28, 28), Vector2(143, 124), "Unsinkable", 16777215);
    mmap.AddGeoMap(99, "discwhole.png", "Whole Disc", Vector2(1, 1), Vector2(1175, 3726), "Terrains", 16777215);
}


void DiscworldFunctions::addDiscworldSpecialRooms(MiniMap& mmap)
{
    RoomData* currentRoom = new RoomData();
    currentRoom->mapId = 8;
    currentRoom->xpos = 46;
    currentRoom->ypos = 179;
    mmap.AddRoom("ShadesEntrance", currentRoom);
}


static int DiscworldFunctions::quowRoomCallback(void *data, int argc, char **argv, char **azColName)
{    

    //RoomData currentRoom = new RoomData();    

    std::stringstream ss;
    for(int i = 0; i<argc; i++)
    {  
        //std::cout<<argv[i]<<std::endl;
        ss << argv[i] << std::endl;
    }

    //Quows rooms table contains -- room_id, map_id, xpos, ypos, room_short,room_type
    std::string room_id;
    ss >> room_id;

    RoomData *thisRoom = new RoomData();
    ss >> (*thisRoom).mapId;
    ss >> (*thisRoom).xpos;
    ss >> (*thisRoom).ypos;
    ss >> (*thisRoom).shortDes;
    ss >> (*thisRoom).roomType;
    thisRoom ->numExits = 0;
    discworldPntr->AddRoom(room_id,thisRoom);
    
    return 0;
}

//*****room_exits SCHEMA
//***********************
// room_id TEXT NOT NULL,
// connect_id TEXT NOT NULL,
// exit TEXT NOT NULL,
// guessed INT NOT NULL,
// PRIMARY KEY (room_id, connect_id)


static int DiscworldFunctions::quowExitsCallback(void *data, int argc, char **argv, char **azColName)
{    

    //RoomData currentRoom = new RoomData();    

    std::stringstream ss;
    
    
    //Quows room_exits table contains room_id,connect_id,exit,guessed
    //We take _only_ the first 3, ignore guessed
    for(int i = 0; i<3; i++)
    {  
        //std::cout<<argv[i]<<std::endl;
        ss << argv[i] << std::endl;
    }

    
    std::string sourceRoomId;
    std::string destRoomId;
    std::string usrInput;
    std::string temp;
    ss >> sourceRoomId;
    ss >> destRoomId;
    ss >> usrInput;
    while(!ss.eof())
    {
        temp = "";
        ss >> temp;
        if(temp.length())
        {
            usrInput.append(" ");
            usrInput.append(temp);
        }
    }

    
    discworldPntr->AddExit(sourceRoomId,destRoomId,usrInput);


    // std::cout<< "sourceRoomId: " << sourceRoomId << std::endl;
    // std::cout<< "destRoomId: " << destRoomId << std::endl;
    // std::cout<< "usrInput: " << usrInput << std::endl;

    return 0;
}

int DiscworldFunctions::addDiscworldRooms(MiniMap* mmap)
{
    //If editied also check/fix "addDiscworldExits" 
    discworldPntr = mmap;

    sqlite3* quowDataBase;
    char *sqlErrorMsg = 0;
    int returnCode;
    const char* data = "Callback function called";
    returnCode = sqlite3_open("./quow/_quowmap_database.db",&quowDataBase);
    if(returnCode)
    {
        std::cout << "Can't open Database"<<std::endl;
        return returnCode;
    }
    returnCode = sqlite3_exec(quowDataBase,"SELECT * from rooms",quowRoomCallback,(void*)data, &sqlErrorMsg);
    sqlite3_close(quowDataBase);

    return returnCode;
}


int DiscworldFunctions::addDiscworldExits(MiniMap* mmap)
{
    //Instead of copy/pasting should have had one function with additional args (callBackFuntion and SQLquery)

    discworldPntr = mmap;

    sqlite3* quowDataBase;
    char *sqlErrorMsg = 0;
    int returnCode;
    const char* data = "Callback function called";
    returnCode = sqlite3_open("./quow/_quowmap_database.db",&quowDataBase);
    if(returnCode)
    {
        std::cout << "Can't open Database"<<std::endl;
        return returnCode;
    }
    returnCode = sqlite3_exec(quowDataBase,"SELECT * from room_exits",quowExitsCallback,(void*)data, &sqlErrorMsg);
    sqlite3_close(quowDataBase);

    return returnCode;
}

void DiscworldFunctions::addDiscworldAliases(MiniMap* mmap)
{
    //The alias I usually use for journey.
    //Should consider loading from a file.
    mmap->AddAlias("jn","journey n");
    mmap->AddAlias("je","journey e");
    mmap->AddAlias("js","journey s");
    mmap->AddAlias("jw","journey w");
    mmap->AddAlias("jne","journey ne");
    mmap->AddAlias("jse","journey se");
    mmap->AddAlias("jsw","journey sw");
    mmap->AddAlias("jnw","journey nw");

    mmap->AddAlias("journey north","journey n");
    mmap->AddAlias("journey east","journey e");
    mmap->AddAlias("journey south","journey s");
    mmap->AddAlias("journey west","journey w");
    mmap->AddAlias("journey northeast","journey ne");
    mmap->AddAlias("journey southeast","journey se");
    mmap->AddAlias("journey southwest","journey sw");
    mmap->AddAlias("journey northwest","journey nw");

    mmap->AddAlias("up","u");
    mmap->AddAlias("down","d");
}

//Thesethree need to work together to get the job done.
// void setupOuterRooms(MiniMap* mmap);
// static void initTerrainsIds()
// static std::vector<std::string> terrainIds;
// static int findTerrainsCallback(void *data, int argc, char **argv, char **azColName);

void DiscworldFunctions::setupOuterRooms(MiniMap* mmap)
{
    //Algorithm Description
    //We want to search for rooms that can be entered from rooms on outer maps
    //To do this we
    //1. Search all rooms in the most outer map for entrances to inner maps
    //i.e. For discworld this is mapid == 99 the terrains
    //2. Set these inner rooms to have the outerroom as the terrains in the right place
    //Also add them to queue 1
    //Make an empty Queue 2
    //Make a hash of reached locations
    //While queue 1 or 2 arn't empty
    //  while queue 1 isn't empty
    //      pop the first elemnt of the queue
    //      for every exit we've not reached ... if it's on the same map add it to queue 1
    //      otherwise add it to queue 2
    //      set it's outermap
    //  while queue 2 isn't empty
    //      pop the first element
    //      for every exit we've not reached ... , if it's in the same map add it to queue 2
    //      otherwise add it to queue 1
    //      set it's outermap

    //Higher level description --
    // We do a breadth first search on the map setting outermaps as we go
    // When we travel to and from two places in the same map, they get the same outermap
    // When we travel from place a to b and they have different maps, b's outermap becomes a.
    // We delay searching new maps until we've fully searched old maps.
    // This is to try to ensure the outermap is the closest exit.
    //
    //Result should be something like, we breadth first search all 
    //depth 1 rooms (Their outerroom is the last outer room) in queue 1
    //We then search all depth 2 rooms, where their outer room is a depth 1 room in queue 2
    //Then we search all depth 3 rooms in queue 1
    //All depth 4 rooms in queue 2
    //Should be done around depth 5 or so, like a secret room in a house in a town in a region in the world.

    initTerrainsIds();
    std::map<std::string, bool> reached;
    std::list<std::string> queue1;
    std::list<std::string> queue2;
    RoomData* currentRoom;
    std::string currentExitId;
    RoomData* currentExitRoom;
    std::string currentRoomId;
    std::string currentInput;
    //For every Terrains id
    for(auto itor = terrainIds.begin(); itor!=terrainIds.end(); itor++)
    {
        //Cout was just used to check I am getting the right ids, looks good to me.
        //std::cout << std::endl << *itor ;
        //std::cout << currentRoom->roomType << " " << currentRoom->shortDes << " " << currentRoom->mapId << " " << *itor <<std::endl;
        currentRoomId = *itor;
        currentRoom = mmap->GetRoom(currentRoomId);
        
        reached.insert({*itor, true});
        //For every exit in the current room
        for(int i = 0; i < currentRoom ->numExits; i++)
        {
            currentExitId = currentRoom->exits[i].roomId;

            currentExitRoom = mmap->GetRoom(currentExitId);
            if(currentExitRoom->mapId != 99)
            {
                reached.insert({currentExitId,true});
                currentInput = currentRoom->exits[i].usrInput;
                mmap->SetOuterRoom(currentExitId,currentRoomId,currentInput);
                queue1.push_back(currentExitId);
            }
            else
            {
                continue;
            }
        }

        //We're checked all rooms you can get to from the Terrains
        //Start checking Queue1 and Queue2 -- Inside rooms.

        while(!queue1.empty() || !queue2.empty())
        {
            //There's stuff in queue 1 or queue 2
            while(!queue1.empty())
            {
                currentRoomId = queue1.front();
                queue1.pop_front();
                currentRoom = mmap->GetRoom(currentRoomId);
                for (int i = 0; i < currentRoom->numExits; i++)
                {
                    currentExitId = currentRoom->exits[i].roomId;
                    if (reached.find(currentExitId) != reached.end())
                        continue; //We already checked this one. Skip it.
                    currentInput = currentRoom->exits[i].usrInput;
                    currentExitRoom = mmap->GetRoom(currentExitId);
                    mmap->SetOuterRoom(currentExitId, currentRoomId, currentInput);
                    if (currentExitRoom->mapId == currentRoom->mapId)
                        queue1.push_back(currentExitId);
                    else
                        queue2.push_back(currentExitId);
                    reached.insert({currentExitId,true});
                }
            }

            while(!queue2.empty())
            {
                currentRoomId = queue2.front();
                queue2.pop_front();
                currentRoom = mmap->GetRoom(currentRoomId);
                for (int i = 0; i < currentRoom->numExits; i++)
                {
                    currentExitId = currentRoom->exits[i].roomId;
                    if (reached.find(currentExitId) != reached.end())
                        continue; //We already checked this one. Skip it.
                    currentInput = currentRoom->exits[i].usrInput;
                    currentExitRoom = mmap->GetRoom(currentExitId);
                    mmap->SetOuterRoom(currentExitId, currentRoomId, currentInput);
                    if (currentExitRoom->mapId == currentRoom->mapId)
                        queue2.push_back(currentExitId);
                    else
                        queue1.push_back(currentExitId);
                    reached.insert({currentExitId,true});
                }
            }
        }

    }
    std::cout << std::endl;
    return;
}



static int DiscworldFunctions::initTerrainsIds()
{
    //We want to
    //select room_id from rooms where map_id == 99;
    //In quows database.
    sqlite3* quowDataBase;
    char *sqlErrorMsg = 0;
    int returnCode;
    const char* data = "Callback function called";
    returnCode = sqlite3_open("./quow/_quowmap_database.db",&quowDataBase);
    if(returnCode)
    {
        std::cout << "Can't open Database"<<std::endl;
        return returnCode;
    }
    returnCode = sqlite3_exec(quowDataBase,"SELECT room_id from rooms WHERE map_id == 99",findTerrainsCallback,(void*)data, &sqlErrorMsg);
    sqlite3_close(quowDataBase);

    return returnCode;

}

static int DiscworldFunctions::findTerrainsCallback(void *data, int argc, char **argv, char **azColName)
{
    //RoomData currentRoom = new RoomData();    

    std::stringstream ss;
    for(int i = 0; i<argc; i++)
    {  
        //std::cout<<argv[i]<<std::endl;
        ss << argv[i] << std::endl;
    }

    std::string room_id;
    ss >> room_id;

    terrainIds.push_back(room_id);
    return 0;
}
