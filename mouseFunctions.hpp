#ifndef MOUSE
#define MOUSE

#include "definitions.hpp"
#include "log.hpp"
#include "API.h"

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

#endif