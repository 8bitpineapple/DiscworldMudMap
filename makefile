OBJS = main.cpp marker.h disctime.cpp discworldfunctions.cpp vector2.cpp geomap.cpp minimap.cpp sdlminimap.cpp discworldminimap.cpp
OBJ_NAME = "build/minimap"
CC = g++
COMPILER_FLAGS= -lSDL2 -lSDL2_image -lsqlite3 -lpthread -lSDL2_ttf
all : $(OBJS)
	$(CC) $(OBJS) -o $(OBJ_NAME) $(COMPILER_FLAGS)
