/*
 * mouseFunctions.c
 *
 *  Created on: May 17, 2025
 *      Author: adamhwu
 */

#include "floodfill_includes/mouseFunctions.h"
#include "movement.h"
#include "values.h"

void updateMousePos(Mouse* mouse) {
    if (mouse->mouseDir == NORTH) {
        mouse->mousePos.y++;
    }
     if (mouse->mouseDir == SOUTH) {
        mouse->mousePos.y--;
     }
     if (mouse->mouseDir == WEST) {
        mouse->mousePos.x--;
     }
    if (mouse->mouseDir == EAST) {
        mouse->mousePos.x++;
     }
}

void move(Maze* maze, Mouse* mouse, Coord* pos) {
    int targetDir;

    if (mouse->mousePos.y - pos->y == 1) {
        targetDir = SOUTH; // best cell is SOUTH
    } else if (mouse->mousePos.x - pos->x == 1) {
        targetDir = WEST;  // best cell is WEST
    } else if (pos->y - mouse->mousePos.y == 1) {
        targetDir = NORTH; // best cell is NORTH
    } else if (pos->x - mouse->mousePos.x == 1) {
        targetDir = EAST;  // best cell is EAST
    }

    int turnsNeeded = (targetDir - mouse->mouseDir + 4) % 4;

    switch (turnsNeeded) {
        case 1:  // 90 degrees right
            turn(1);
            break;
        case 2:  // 180 degrees
            turn180();
            break;
        case 3:  // 90 degrees left
            turn(0);
            break;
        default: // case 0, no turn needed
            break;
    }
    mouse->mouseDir = (Direction)(targetDir);  // Update the mouse direction
}
