#include "floodfill_includes/mouseFunctions.h"

//only called after moving, updates the mouse's coordinates
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

/* if the difference between the mouse position and the best cell is 1, we know we must move there.*
 * E.g. mouse is in (4,6), the best cell (calculated by getBestCell) is (5, 6). This function finds
 * the difference between 4 and 5, as well as the direction via the if statements.
 */
void move(Maze* maze, Mouse* mouse, Coord* bestCell) {
    int targetDir;

    if (mouse->mousePos.y - bestCell->y == 1) {
        targetDir = SOUTH; // best cell is SOUTH
    } else if (mouse->mousePos.x - bestCell->x == 1) {
        targetDir = WEST;  // best cell is WEST
    } else if (bestCell->y - mouse->mousePos.y == 1) {
        targetDir = NORTH; // best cell is NORTH
    } else if (bestCell->x - mouse->mousePos.x == 1) {
        targetDir = EAST;  // best cell is EAST
    }

    /*e.x. targetDir is NORTH, mouseDir is currently SOUTH, therefore (0-2+4)= 2, 2 % 4 results in 2, which is a 180 turn.*/
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

    // 180mm is the length of one cell in the actual maze.
    move_dist(180);
}
