#include "stdlib.h"

#include "definitions.h"
#include "mazeFunctions.h"
#include "values.h"

void initializeEverything(Maze* myMaze, Mouse* myMouse) {

    myMaze->goalPos.x = 0;
    myMaze->goalPos.y = 0;
    myMouse->mouseDir = NORTH;

    for (int x = 0; x < 16; x++) {
        for (int y = 0; y < 16; y++) {

            myMaze->cellWalls[x][y] = 0;
            myMaze->distances[x][y] = 255;
            myMaze->goalPos.x = 7;
            myMaze->goalPos.y = 8;


            if (x == 0) {
            	//west boundary hardcoded
            	myMaze->cellWalls[x][y] = 0b1000;
            }

            if (x == 15) {
            	//east boundary hardcoded
            	myMaze->cellWalls[x][y] = 0b0100;
            }

            if (y == 0) {
            	//south boundary hardcoded
            	myMaze->cellWalls[x][y] = 0b0010;
            }

            if (y == 15) {
            	//north boundary hardcoded
            	myMaze->cellWalls[x][y] = 0b0001;
            }
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

void setGoalCenter (Mouse* mouse, Maze* maze){
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
}

void setGoalPos (Coord coord, Maze* maze) {
    maze->goalPos.x = coord.x;
    maze->goalPos.y = coord.y;
}
