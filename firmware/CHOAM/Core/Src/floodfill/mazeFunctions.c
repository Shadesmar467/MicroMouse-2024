#include "stdlib.h"
#include "floodfill_includes/mazeFunctions.h"
#include "distance.h"

//initializes maze start values (borders, wall values set to 0, goal cell set as center, mouse initial direction north)
void init_maze(Maze* maze, Mouse* mouse) {

    mouse->mousePos = initialCoord;
    mouse->mouseDir = NORTH;

    for (int x = 0; x < 16; x++) {
        for (int y = 0; y < 16; y++) {

            maze->cellWalls[x][y] = (x == 0) ? WEST_MASK : 0;
            maze->cellWalls[x][y] = (x == 15) ? EAST_MASK : 0;
            maze->cellWalls[x][y] = (y == 0) ? SOUTH_MASK : 0;
            maze->cellWalls[x][y] = (y == 15) ? NORTH_MASK : 0;

            maze->distances[x][y] = 255;

            maze->goalPos.x = 7;
            maze->goalPos.y = 8;
        }
    }
}

void scan_walls(Maze* maze, Mouse* mouse) {
    // ^^need a pointer to affect the og mouse and maze, instead of making a copy
    const int rightMasks[] = {EAST_MASK, SOUTH_MASK, WEST_MASK, NORTH_MASK}; // order of these lists matter
    const int leftMasks[] = {WEST_MASK, NORTH_MASK, EAST_MASK, SOUTH_MASK}; // NESW order, based on the current DIRECTION of the mouse
    const int frontMasks[] = {NORTH_MASK, EAST_MASK, SOUTH_MASK, WEST_MASK};

    /* mouseDir is an enum, from 0 to 3. By shifting the order of the directions we can select the correct wall and add it to the cell.
     * For example, if the mouse is facing EAST, this is the value 1. If, while facing east, we detect a wall to the RIGHT of the mouse,
     * the third statement gets triggered and we calculate rightMasks[1]. This is the value SOUTH_MASK, and it is bitwise or'd to the
     * current wall value to update it.*/
    if (wallDetectFront()) {
        maze->cellWalls[mouse->mousePos.x][mouse->mousePos.y] |= frontMasks[mouse->mouseDir];
    }
    if (wallDetectLeft()) {
        maze->cellWalls[mouse->mousePos.x][mouse->mousePos.y] |= leftMasks[mouse->mouseDir];
    }
    if (wallDetectRight()) {
        maze->cellWalls[mouse->mousePos.x][mouse->mousePos.y] |= rightMasks[mouse->mouseDir];

    }
    //at this point, the mouses current cell now contains a binary number that tells us which walls exist
}

//sets 1 of 4 center cells to a goal position based on mouse quadrant.
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

//allows us to set the goal position to anywhere in the maze for wall finding
void setGoalPos (Coord coord, Maze* maze) {
    maze->goalPos.x = coord.x;
    maze->goalPos.y = coord.y;
}
