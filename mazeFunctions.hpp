#ifndef MAZE
#define MAZE

#include <iostream>
#include <string>

#include "stdlib.h"

#include "API.h"
#include "definitions.hpp"
#include "log.hpp"

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
}

void updateSim (Maze* mazePtr, Mouse* mousePtr) {
    for (int x = 0; x < 16; x++) {
        for (int y = 0; y < 16; y++) {
            if (mazePtr->cellWalls[y][x] & NORTH_MASK) {
                // API set walls for some direction
                API::setWall(mousePtr->mousePos.x, mousePtr->mousePos.y, 'n');
            }
            if (mazePtr->cellWalls[y][x] & EAST_MASK){
                API::setWall(mousePtr->mousePos.x, mousePtr->mousePos.y, 'e');
            }
            if (mazePtr->cellWalls[y][x] & SOUTH_MASK) {
                API::setWall(mousePtr->mousePos.x, mousePtr->mousePos.y, 's');
            }
            if (mazePtr->cellWalls[y][x] & WEST_MASK) {
                API::setWall(mousePtr->mousePos.x, mousePtr->mousePos.y, 'w');
            }
        }
    }
    mazePtr->cellWalls[mousePtr->mousePos.x][mousePtr->mousePos.y] = 0;
}

int calcManDist (int x2, int x1, int y2, int y1) {
    return abs(x2-x1) - abs(y2-y1);
}

void setManDist(Maze* maze){

    int closestX;
    int closestY;
    int x;
    int y;

    for (x=0; x < 16; x++) {
        for (y=0; y < 16; y++) {
            if (x >= 8 && y >= 8){
                closestX = 8;
                closestY = 8;
            } else if (x < 8 && y >= 8) {
                closestX = 7;
                closestY = 8;
            } else if (x < 8 && y < 8) {
                closestX = 7;
                closestY = 7;
            } else if (x >= 8 && y < 8) {
                closestX = 8;
                closestY = 7;
            }
            maze->distances[x][y] = calcManDist(closestX, x, closestY, y);
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
