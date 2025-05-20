#include <stdbool.h>
#include "stdlib.h"

#include "floodfill_includes/utilityFunctions.h"
#include "floodfill_includes/mouseFunctions.h"
#include "floodfill_includes/mazeFunctions.h"
#include "floodfill_includes/floodfill.h"
#include "movement.h"
#include "values.h"


//initializes a virtual queue for processing adjacent cells
//insane naming convention
void initQ(Queue* q) {
    for (int x = 0; x < 255; x++) {
            q->kew[x].pos = initialCoord;
    }
}

//input a coordinate C, get back neighbors
CellList* getNeighborCells(Maze* mazePtr, Coord c) {

    CellList* list = (CellList*)malloc(sizeof(CellList));
    //this is a cell list named list allocating memory for all cells in the list

    int dirX[] = {0, 1, 0, -1}; //order matters, see below
    int dirY[] = {1, 0, -1, 0};

    int count = 0;

    //the following if statement is for identifying number of neighbor cells
    if ((c.x == 15 || c.x == 0) && (c.y == 0 || c.y == 15)) {
        count = 2; //corner cells
    } else if (c.x == 15 || c.x == 0 || c.y == 0 || c.y == 15) {
        count = 3; //edge cells
    } else {
        count = 4; //regular cells (4 neighbors)
    }

    list->cells = (Cell*)malloc(count * sizeof(Cell)); //now we know how much memory to allocate for the neighbor cells
    list->size = 0;

    //now i need to calculate the new coordinates of each cell and store the cell in the array
    for (int i = 0; i < 4; i++) {
        int newX = c.x + dirX[i]; //the order of dirX and Y allow us to run through all neighbors efficiently
        int newY = c.y + dirY[i];

        /* necessary to check twice. e.x. cell (8,3) is identified to have a wall SOUTH, while the mouse is in (8,2).
         * Both (8, 3) SOUTH wall and (8, 2) NORTH wall must be updated to reflect this change. */
        bool currWall = (mazePtr->cellWalls[c.x][c.y] & dir_mask[i]); //whether current cell has a wall blocking
        bool neighborWall = (mazePtr->cellWalls[newX][newY] & ndir_mask[i]); //whether neighbor cell has a wall blocking

        //checking if the coordinate is blocked or not
        if (newX >= 0 && newX < 16 && newY >= 0 && newY < 16) { //if cell is in the maze boundaries
            if (!currWall && !neighborWall){  // if new cell is NOT blocked by a wall
                list->cells[list->size].pos.x = newX;
                list->cells[list->size].pos.y = newY; //then finally add to the cell list
                list->size++; //increment cell list size
            }
        }
    }
    return list;
}

//obtains the best cell
Coord getBestGoalCell(Maze* mazePtr, Mouse* mousePtr) {
    Coord best_cell_coord; // return object
    Coord current_coord = mousePtr->mousePos;
    CellList* neighbors = getNeighborCells(mazePtr, current_coord); // grab neighbors not blocked by walls

    // the cell the mouse should move to has a distance equal to current distance-1, in respect to the goal.
    int desired_cell_cost = mazePtr->distances[current_coord.x][current_coord.y] - 1;

    for (int i = 0; i < neighbors->size; i++) { // iterate through the neighbors
        Coord test_cell_coord = neighbors->cells[i].pos;
        int test_cell_cost = mazePtr->distances[test_cell_coord.x][test_cell_coord.y];

        if (test_cell_cost == desired_cell_cost)   // if the cost is 1 less than the current one...
            best_cell_coord = test_cell_coord; // ... then we know this is the best cell!
        	//note: in case of a tie the mouse picks the cell it IDs first
    }
    return best_cell_coord;
}

//used for getting back to the start position
Coord getBestStartCell(Maze* mazePtr, Mouse* mousePtr) {
    Coord best_cell_coord;  // return object
    Coord current_coord = mousePtr->mousePos;
    CellList* neighbors = getNeighborCells(mazePtr, current_coord);     // grab neighbors not blocked by walls

    int desired_cell_cost = mazePtr->distances[current_coord.x][current_coord.y] + 1;

    for (int i = 0; i < neighbors->size; i++) {     // iterate through the neighbors
        Coord test_cell_coord = neighbors->cells[i].pos;
        int test_cell_cost = mazePtr->distances[test_cell_coord.x][test_cell_coord.y];

        if (test_cell_cost == desired_cell_cost)   // if the cost is 1 MORE than the current one
            best_cell_coord = test_cell_coord;
    }
    return best_cell_coord;
}

// currently not used
Coord chooseRandomCell(Maze* mazePtr, Mouse* mousePtr) {
    Coord random_cell_coord;  // return object
    Coord current_coord = mousePtr->mousePos;
    CellList* neighbors = getNeighborCells(mazePtr, current_coord);     // grab neighbors not blocked by walls

    random_cell_coord = neighbors->cells[0].pos;

    return random_cell_coord;
}

// used for identifying deadends
int countOnes(unsigned int n) { // counts how many ones are in a binary number
    int count = 0;
    while (n) {
        count += n & 1;
        n = n >> 1;
    }
    return count;
}

// checks if current cell is a dead end
void deadEndID(Maze* mazePtr, Mouse* mousePtr) {
    int curCellWalls = mazePtr->cellWalls[mousePtr->mousePos.x][mousePtr->mousePos.y];

    //checking for a dead end (which always has 3 walls)
    if (countOnes(curCellWalls) == 3) {
        mousePtr->isInDeadEnd = true;   // store in mouse whether we are in a dead end
    }
}

// sets wall if we are at the mouth of the dead end
void wallIntersectionTest(Maze* mazePtr, Mouse* mousePtr) {
    int curCellWall = mazePtr->cellWalls[mousePtr->mousePos.x][mousePtr->mousePos.y];

    //if dead end is true we know we are returning from a dead end
    if (countOnes(curCellWall) <= 1) { //if mouse is in the intersection
        //set a wall behind the mouse in the current cell
        Coord prevPos = mousePtr->mousePos;
        switch (mousePtr->mouseDir) {
            case NORTH:
                prevPos.y -= 1;
                curCellWall |= SOUTH_MASK;
                break;
            case EAST:
                prevPos.x += 1;
                curCellWall |= WEST_MASK;
                break;
            case SOUTH:
                prevPos.y += 1;
                curCellWall |= NORTH_MASK;
                break;
            case WEST:
                prevPos.x -= 1;
                curCellWall |= EAST_MASK;
                break;
        }

        mousePtr->isInDeadEnd = false;
    }
}

// blocks off dead ends with a wall so the mouse will not go there again
void deadEndCheck (Maze* mazePtr, Mouse* mousePtr) {
    Coord curPos = mousePtr->mousePos;
    if (!((curPos.x == 0 && curPos.y == 0))) { //check if we are in starting cell
        if (mousePtr->isInDeadEnd) {     // if in dead end, check if we are at the end of it
            wallIntersectionTest(mazePtr, mousePtr);
        }
        else {
            deadEndID(mazePtr, mousePtr); // otherwise, check if we're in a dead end
        }
    } else { //impossible for dead end to be in starting cell
        mousePtr->isInDeadEnd = false;
    }
}

//meat of mouse navigation, combines previous functions to navigate the maze
int goToPos(int goalIsCenter, Maze* myMaze, Mouse* myMouse){
	while (true) {
		if (goalIsCenter){
			setGoalCenter(myMouse, myMaze);
		}
		scanWalls(myMaze, myMouse);
		deadEndCheck(myMaze, myMouse);
		floodFill(myMaze);

		Coord bestCell = getBestGoalCell(myMaze, myMouse);

		move(myMaze, myMouse, &bestCell);
		updateMousePos(myMouse);

		if (myMouse->mousePos.x == myMaze->goalPos.x && myMouse->mousePos.y == myMaze->goalPos.y) {
			//it is finished.
			break;
			//LISAN AL GAIB
		}
	}
	scan_walls(myMaze, myMouse);
//		deadEndCheck(myMaze, myMouse);
	floodFill(myMaze);
	Coord bestCell = getBestGoalCell(myMaze, myMouse);
	move(myMaze, myMouse, &bestCell);
	updateMousePos(myMouse);

	if (myMouse->mousePos.x == myMaze->goalPos.x && myMouse->mousePos.y == myMaze->goalPos.y) {
		return 0;
	}
    return 1;
}
