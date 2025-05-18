#ifndef MAZE
#define MAZE

#include "stdlib.h"

#include "API.h"
#include "definitions.hpp"

void initializeEverything(Maze* maze, Mouse* mouse) {

    mouse->mousePos = {0,0};
    mouse->mouseDir = NORTH;

    for (int x = 0; x < 16; x++) {
        for (int y = 0; y < 16; y++) {

            maze->cellWalls[x][y] = 0;
            maze->distances[x][y] = 255;
            maze->goalPos = {7,8};

            API::setWall(0, y, 'w'); 
            API::setWall(15, y, 'e'); 
            API::setWall(x, 0, 's');
            API::setWall(x, 15, 'n');
        }
    }
}

void scanWalls(Maze* maze, Mouse* mouse) { 
    // ^^need a pointer to affect the og mouse and maze, instead of making a copy
    const int rightMasks[] = {EAST_MASK, SOUTH_MASK, WEST_MASK, NORTH_MASK};
    const int leftMasks[] = {WEST_MASK, NORTH_MASK, EAST_MASK, SOUTH_MASK};
    const int frontMasks[] = {NORTH_MASK, EAST_MASK, SOUTH_MASK, WEST_MASK};

    if (API::wallFront()) {
        maze->cellWalls[mouse->mousePos.x][mouse->mousePos.y] |= frontMasks[mouse->mouseDir];
    }
    if (API::wallRight()) {
        maze->cellWalls[mouse->mousePos.x][mouse->mousePos.y] |= rightMasks[mouse->mouseDir];
    }
    if (API::wallLeft()) {
        maze->cellWalls[mouse->mousePos.x][mouse->mousePos.y] |= leftMasks[mouse->mouseDir];
    }
    //at this point, the mouses current cell now contains a binary number that tells us which walls exist
}

void updateSim (Maze* maze, Mouse* mouse) {
    for (int x = 0; x < 16; x++) {
        for (int y = 0; y < 16; y++) {
            if (maze->cellWalls[x][y] & NORTH_MASK) {
                API::setWall(x, y, 'n');
            }
            if (maze->cellWalls[x][y] & EAST_MASK){
                API::setWall(x, y, 'e');
            }
            if (maze->cellWalls[x][y] & SOUTH_MASK) {
                API::setWall(x, y, 's');
            }
            if (maze->cellWalls[x][y] & WEST_MASK) {
                API::setWall(x, y, 'w');
            }
        }
    }
}

void setGoalCenter (Mouse* mouse, Maze* maze){
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

void setGoalPos (Coord coord, Maze* maze) {
    maze->goalPos.x = coord.x;
    maze->goalPos.y = coord.y;
}

#endif
