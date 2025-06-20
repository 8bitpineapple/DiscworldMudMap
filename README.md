**⚠️ This project is a work in progress.**  
While it's already functional, it's still evolving and may have rough edges.


# DiscworldMudMap
A map viewer of Terry Pratchett's Discworld as it appears in the [Discworld MUD](http://discworld.starturtle.net/lpc/).
For use with Tintin++ but potentially other MUD clients.
![MiniMap Image](https://i.imgur.com/qcTfmhu.png)

This map is largely based on [Quow's Quow Bar](https://quow.co.uk/minimap.php), a Mush Client Plugin . I like Quow's use of Kefka's/Airk's maps for a minimap but arn't that interested in using Mush Client, I'm using the files in his plugin to render a map in a standalone SDL2 application that will be usable in other clients.

I make use of map images by [Kefka](https://dw.daftjunk.com/) , Airk, and [Quow](http://www.quow.co.uk/). Some edits by me E.g. nicer fonts and keeping road colours consistant.
I also use Quows SQL database to initially load in information about rooms and information about the map png's.

Also credit to Oki as I'm using [Oki's TinTin++ Mud Client scripts](https://fossil.tubul.net/tt_dw/doc/trunk/README.md).

This is mostly a personal project but if anyone else wants to try to use it feel free.
When I consider the map feature complete I'll start trying to make it more user friendly to download/install and see if I can make it useful to more MUD clients.

# Usage
The map by default starts inside the Drum. From there you can change your position by writing in the console:
 - Writing an exit to travel there.
 - Writing a roomid to teleport to that room id.
 - "zoomout" will teleport to the room outside the room your in. E.g. Using zoomout will take you to the room outside the drum in AM, using zoomout in AM will take you to the sto plains map, and using zoomout in the sto plains map will take you to the world map.
 - q to quit.
 
While you can launch the application on it's own it's intended to be used in conjunction with a MUD client.
I'm using it with Tintin++ as Tintin++ can launch console applications and send inputs to them. (I'm not sure whether this is possible with other clients,
I may have to add other interprocess communication options for other clients.)
Right now I am launching my minimap in Tintin++ as #minimap, I then use scripts in TinTin++ to control the minimap

# Tintin++ examples
Start the minimap
```
#run {minimap} {/home/bradley/Documents/MUD/Discworld/scripts/minimap};
```
Start sending all user inputs to minimap
``` 
#EVENT {SEND OUTPUT} {#minimap %0};
```
Teleport the minimap to look at \<room id>
``` 
#minimap <room id>
```
Add a /syncMap function to center the map on the position the player is. (Makes use of the function @current_room_id found in Oki's /scripts/map/identifiers.tin)
```  
#alias {/syncMap} {#minimap @current_room_id{}}
```
Keep the current position on top of the player (I'm sure they'll be a much better way to do this)
```  
#alias /startMapTicker {#TICKER {minimapUpdater} {#minimap @current_room_id{}} {0.3}}
```
Stop following the player
```  
#alias /stopMapTicker {#UNTICKER {minimapUpdater} }
```
You can bind any of these functions to keys using Tintin++ macros, e.g.
  ```  
#macro \e[23~ /startMapTicker
#macro \e[24~ /stopMapTicker
  ```  
Binds f11 and f12 to start/stop following your position.

  
These scripts are functional but still evolving — they work well as a base, but may need refinement.
The map is by default Always on top, so you can position it above your client.
![tintin++ Client with DiscworldMudMap on top](https://i.imgur.com/1yithYV.png)
   
# Installation / Compilation
Right now the Makefile is setup so that you can compile on Linux using make and run the resulting binary in build/minimap.
To copy the map somewhere else be sure to also copy /maps/ and /quow/ inside the build directory.

Current dependencies include:
 - libsdl2-dev
 - libsdl2-image-dev
 - libsqlite3-dev
 - libsdl2-ttf-dev
 - The g++ compiler.

SDL2 is used for displaying the map and libsqlite3 is used for reading Quows SDL database.

On a ubuntu based distribution you should be able to install dependencies with:
- ```sudo apt-get install libsdl2-dev ```  
- ```sudo apt-get install libsdl2-image-dev``` 
- ```sudo apt-get install libsqlite3-dev``` 
- ```sudo apt-get install libsdl2-ttf-dev```
- ```sudo apt install g++``` 

And then finally:
- ```make``` 
- Copy the contents of ./build/ to wherever you'd like.

# Roadmap / Planned Features
- Add alternate IPC methods for clients that can't launch binaries
- Improve auto-follow functionality
- Cross-platform support
- Precompiled binaries or installer script

