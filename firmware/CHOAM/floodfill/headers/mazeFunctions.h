#ifndef MAZE
#define MAZE

#include "definitions.h"

void initializeEverything(Maze* myMaze, Mouse* myMouse);

void scanWalls(Maze* mazePtr, Mouse* mousePtr);

void setGoalCenter (Mouse* mouse, Maze* maze);

void setGoalPos (Coord coord, Maze* maze);

#endif
