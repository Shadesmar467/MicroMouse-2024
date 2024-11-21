#ifndef Dir
#define Dir

#include <iostream>
#include <string>

#include "log.hpp"
#include "definitions.hpp"

void directionCheck(Mouse* mouse) {
    if (mouse->mouseDir == NORTH){
        log("NORTH");
    } 
    if (mouse->mouseDir == EAST) {
        log("EAST");
    }
    if (mouse->mouseDir == SOUTH) {
        log("SOUTH");
    }
    if (mouse->mouseDir == WEST) {
        log("WEST");
    }
}

void positionCheck(Coord mousePosition) {
    log("position changed");
}

void initTestMaze(Maze* mazePtr, Mouse* mousePtr) {
    std::cerr << "initalizing test masze... ";
    mazePtr->cellWalls[6][6] = 1;
    mazePtr->cellWalls[7][6] = 10;
    mazePtr->cellWalls[8][6] = 10;
    mazePtr->cellWalls[9][6] = 6;
    mazePtr->cellWalls[6][7] = 13;
    mazePtr->cellWalls[7][7] = 3;
    mazePtr->cellWalls[8][7] = 6;
    mazePtr->cellWalls[9][7] = 1;
    mazePtr->cellWalls[6][8] = 7;
    mazePtr->cellWalls[7][8] = 9;
    mazePtr->cellWalls[8][8] = 4;
    mazePtr->cellWalls[9][8] = 1;
    mazePtr->cellWalls[6][9] = 0;
    mazePtr->cellWalls[7][9] = 14;
    mazePtr->cellWalls[8][9] = 9;
    mazePtr->cellWalls[9][9] = 12;
} 
  
#endif