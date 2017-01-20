#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAZESIZE 100
#define WALL '#' 
#define ROAD '.' 
#define GOODWAY 'X'
#define UNVISITED 'R'
#define ENTRANCE 'I'
#define EXIT 'O' 

#define UP if (maze[posx-2][posy] == UNVISITED)\
{\
    maze[posx-1][posy] = ROAD;\
    digWall(maze, posx-2, posy);\
} break
#define DOWN if (maze[posx+2][posy] == UNVISITED)\
{\
    maze[posx+1][posy] = ROAD;\
    digWall(maze, posx+2, posy);\
} break
#define LEFT if (maze[posx][posy-2] == UNVISITED)\
{\
    maze[posx][posy-1] = ROAD;\
    digWall(maze, posx, posy-2);\
} break
#define RIGHT if (maze[posx][posy+2] == UNVISITED)\
{\
    maze[posx][posy+1] = ROAD;\
    digWall(maze, posx, posy+2);\
} break

void mazeGenerator(char maze[][MAZESIZE]);
void digWall(char maze[][MAZESIZE], int posx, int posy);
void mazeTraverse(char maze[][MAZESIZE], int posx, int posy);