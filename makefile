OBJS = main.cpp discworldfunctions.cpp vector2.cpp geomap.cpp minimap.cpp sdlminimap.cpp discworldminimap.cpp
OBJ_NAME = "build/minimap"
CC = g++
COMPILER_FLAGS= -lSDL2 -lSDL2_image -lsqlite3 -lpthread
all : $(OBJS)
	$(CC) $(OBJS) -o $(OBJ_NAME) $(COMPILER_FLAGS)
