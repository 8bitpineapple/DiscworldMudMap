#include <string>
typedef uint32_t Uint32;

struct MapPosition
{
    int x = 0;
	int y = 0;
    int mapId = 0;
    //NOTE somtimes we might not know roomId
    std::string roomId = "";
};

//A marker is a marked position, e.g. highliged with a colour or something like that.
struct Marker : MapPosition
{
	int h = 25;
	int w = 25;
	Uint32 colour = 0x000000;
};

