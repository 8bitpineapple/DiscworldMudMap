#include "discworldminimap.h"
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
