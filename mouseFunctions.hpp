#ifndef MOUSE
#define MOUSE

#include "definitions.hpp"
#include "log.hpp"
#include "API.h"
#include "testFunctions.hpp"

#include <iostream>
#include <string>

void updateMousePos(Mouse* mouse) {
    if (mouse->mouseDir == NORTH) {
        mouse->mousePos.y++;
        log("y+1");
        API::setColor(mouse->mousePos.x, mouse->mousePos.y, 'G');
    }
     if (mouse->mouseDir == SOUTH) {
        mouse->mousePos.y--;
        log("y-1");
        API::setColor(mouse->mousePos.x, mouse->mousePos.y, 'G');
     } 
     if (mouse->mouseDir == WEST) {
        mouse->mousePos.x--;
        log("x-1");
        API::setColor(mouse->mousePos.x, mouse->mousePos.y, 'G');
     }
    if (mouse->mouseDir == EAST) {
        mouse->mousePos.x++;
        log("x+1");
        API::setColor(mouse->mousePos.x, mouse->mousePos.y, 'G');
     }
}

Direction mTurnLeft(Mouse* mouse) {
    return static_cast<Direction>((mouse->mouseDir + 3) % 4);
}

Direction mTurnRight(Mouse* mouse) {
    return static_cast<Direction>((mouse->mouseDir + 1) % 4);
}

/*void move(Maze* maze, Mouse* mouse, Coord inC) {

    int targetCell;

    if (mouse->mousePos.y - inC.y == 1){ // best cell is SOUTH 
        if (mouse->mouseDir == WEST) API::turnLeft();
        if (mouse->mouseDir == NORTH){
            API::turnLeft();
            API::turnLeft();
        }
        if (mouse->mouseDir == EAST) API::turnRight();
        //if mouse facing south just move forward
    }
    else if (mouse->mousePos.x - inC.x == 1) { // best cell is WEST
        if (mouse->mouseDir == NORTH) API::turnLeft();
        if (mouse->mouseDir == EAST) {
            API::turnLeft();
            API::turnLeft();
        }
        if (mouse->mouseDir == SOUTH) API::turnRight();
    }
    else if (inC.y - mouse->mousePos.y == 1) { // best cell is NORTH
        if (mouse->mouseDir == EAST) API::turnLeft();
        if (mouse->mouseDir == SOUTH) {
            API::turnLeft();
            API::turnLeft();
        }
        if (mouse->mouseDir == WEST) API::turnRight();
    }
    else if (inC.x - mouse->mousePos.x == 1) { // best cell is EAST
        if (mouse->mouseDir == SOUTH) API::turnLeft();
        if (mouse->mouseDir == WEST) {
            API::turnLeft();
            API::turnLeft();
        }
        if (mouse->mouseDir == NORTH) API::turnRight();
    }

    API::moveForward();
}*/

void move(Maze* maze, Mouse* mouse, Coord inC) {
    int targetDir;

    if (mouse->mousePos.y - inC.y == 1) {
        targetDir = SOUTH; // best cell is SOUTH
    } else if (mouse->mousePos.x - inC.x == 1) {
        targetDir = WEST;  // best cell is WEST
    } else if (inC.y - mouse->mousePos.y == 1) {
        targetDir = NORTH; // best cell is NORTH
    } else if (inC.x - mouse->mousePos.x == 1) {
        targetDir = EAST;  // best cell is EAST
    }

    int turnsNeeded = (targetDir - mouse->mouseDir + 4) % 4;

    switch (turnsNeeded) {
        case 1:  // 90 degrees right
            API::turnRight();
            break;
        case 2:  // 180 degrees
            API::turnLeft();
            API::turnLeft();
            break;
        case 3:  // 90 degrees left
            API::turnLeft();
            break;
        default: // case 0, no turn needed
            break;
    }

    mouse->mouseDir = static_cast<Direction>(targetDir);  // Update the mouse direction
    directionCheck(mouse);
    API::moveForward();
}

#endif