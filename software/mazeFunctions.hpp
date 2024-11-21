#ifndef MAZE
#define MAZE

#include <iostream>
#include <string>

#include "stdlib.h"

#include "API.h"
#include "definitions.hpp"
#include "log.hpp"

void initializeEverything(Maze* myMaze, Mouse* myMouse) {
    
    myMouse->mousePos = {0,0};
    myMouse->mouseDir = NORTH;
    
    for (int x = 0; x < 16; x++) {
        for (int y = 0; y < 16; y++) {

            myMaze->cellWalls[x][y] = 0;
            myMaze->distances[x][y] = 255;
            myMaze->goalPos = {7,8};

                API::setWall(0, y, 'w'); 
                API::setWall(15, y, 'e'); 
                API::setWall(x, 0, 's');
                API::setWall(x, 15, 'n');
        }
    }
}

void scanWalls(Maze* mazePtr, Mouse* mousePtr) { 
// ^^need a pointer to affect the og mouse and maze, instead of making a copy
    const int rightMasks[] = {EAST_MASK, SOUTH_MASK, WEST_MASK, NORTH_MASK};
    const int leftMasks[] = {WEST_MASK, NORTH_MASK, EAST_MASK, SOUTH_MASK};
    const int frontMasks[] = {NORTH_MASK, EAST_MASK, SOUTH_MASK, WEST_MASK};

    if (API::wallFront()) {
        mazePtr->cellWalls[mousePtr->mousePos.x][mousePtr->mousePos.y] |= frontMasks[mousePtr->mouseDir];
    }
    if (API::wallRight()) {
        mazePtr->cellWalls[mousePtr->mousePos.x][mousePtr->mousePos.y] |= rightMasks[mousePtr->mouseDir];
    }
    if (API::wallLeft()) {
        mazePtr->cellWalls[mousePtr->mousePos.x][mousePtr->mousePos.y] |= leftMasks[mousePtr->mouseDir];
    }
    //at this point, the mouses current cell now contains a binary number that tells us which walls exist
}

void updateSim (Maze* mazePtr, Mouse* mousePtr) {
    for (int x = 0; x < 16; x++) {
        for (int y = 0; y < 16; y++) {
            if (mazePtr->cellWalls[x][y] & NORTH_MASK) {
                // API set walls for some direction
                API::setWall(x, y, 'n');
            }
            if (mazePtr->cellWalls[x][y] & EAST_MASK){
                API::setWall(x, y, 'e');
            }
            if (mazePtr->cellWalls[x][y] & SOUTH_MASK) {
                API::setWall(x, y, 's');
            }
            if (mazePtr->cellWalls[x][y] & WEST_MASK) {
                API::setWall(x, y, 'w');
            }
        }
    }
}

void setGoalPos (Mouse* mouse, Maze* maze){
    API::clearColor(maze->goalPos.x, maze->goalPos.y);
    int closestX;
    int closestY;
            if (mouse->mousePos.x >= 8 && mouse->mousePos.y >= 8){
                closestX = 8;
                closestY = 8;
            } else if (mouse->mousePos.x < 8 && mouse->mousePos.y >= 8) {
                closestX = 7;
                closestY = 8;
            } else if (mouse->mousePos.x < 8 && mouse->mousePos.y < 8) {
                closestX = 7;
                closestY = 7;
            } else if (mouse->mousePos.x >= 8 && mouse->mousePos.y < 8) {
                closestX = 8;
                closestY = 7;
            }
            maze->goalPos.x = closestX;
            maze->goalPos.y = closestY;
            API::setColor(maze->goalPos.x, maze->goalPos.y, 'O');
}
#endif
