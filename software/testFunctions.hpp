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

#endif