#include <string>
typedef uint32_t Uint32;

//Marker struct contains data for drawing on a map.
struct marker
{
	int x = 0;
	int y = 0;
	int h = 25;
	int w = 25;
	int mapId = 0;
	Uint32 colour = 0x000000;
//Room Id may be used for getting extra information about the marker.
//And initialising x,y,h,w,
//NOTE somtimes we might mark coordinates we don't know the roomId
	std::string roomId = "";
};

