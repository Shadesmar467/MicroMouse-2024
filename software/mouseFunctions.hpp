#ifndef MOUSE
#define MOUSE

#include "definitions.hpp"
#include "API.h"

void updateMousePos(Mouse* mouse) {
    if (mouse->mouseDir == NORTH) {
        mouse->mousePos.y++;
        API::setColor(mouse->mousePos.x, mouse->mousePos.y, 'G');
    }
     if (mouse->mouseDir == SOUTH) {
        mouse->mousePos.y--;
        API::setColor(mouse->mousePos.x, mouse->mousePos.y, 'G');
     } 
     if (mouse->mouseDir == WEST) {
        mouse->mousePos.x--;
        API::setColor(mouse->mousePos.x, mouse->mousePos.y, 'G');
     }
    if (mouse->mouseDir == EAST) {
        mouse->mousePos.x++;
        API::setColor(mouse->mousePos.x, mouse->mousePos.y, 'G');
     }
}

void move(Maze* maze, Mouse* mouse, Coord* inC) {
    bool dead; //for wall-checking
    int targetDir;

    if (mouse->mousePos.y - inC->y == 1) {
        targetDir = SOUTH; // best cell is SOUTH
    } else if (mouse->mousePos.x - inC->x == 1) {
        targetDir = WEST;  // best cell is WEST
    } else if (inC->y - mouse->mousePos.y == 1) {
        targetDir = NORTH; // best cell is NORTH
    } else if (inC->x - mouse->mousePos.x == 1) {
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
    //directionCheck(mouse);
    API::moveForward();
    
    

}

#endif
