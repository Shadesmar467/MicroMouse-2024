#ifndef UTIL
#define UTIL

#include <iostream>
#include <stdbool.h>

#include "stdlib.h"

#include "API.h"
#include "definitions.hpp"

void initQ(Queue* q) {
    for (int x = 0; x < 255; x++) {
            q->kew[x] = {0};
    }
}

CellList* getNeighborCells(Maze* mazePtr, Coord c) { //input a coordinate C, get back neighbors
    
    CellList* list = (CellList*)malloc(sizeof(CellList));
    //this is a cell list named list allocating memory for all cells in the list

    int dirX[] = {0, 1, 0, -1};
    int dirY[] = {1, 0, -1, 0};

    int count = 0;  
    char test[20];

    //the following if statement is for calculating size of the allocated memory
    if ((c.x == 15 || c.x == 0) && (c.y == 0 || c.y == 15)) {
        count = 2;
    } else if (c.x == 15 || c.x == 0 || c.y == 0 || c.y == 15) {
        count = 3;
    } else {
        count = 4;
    }

    list->cells = (Cell*)malloc(count * sizeof(Cell));
    list->size = 0;

    //now i need to calculate the new coordinates of each cell and store the cell in the array
    for (int i = 0; i < 4; i++) {
        int newX = c.x + dirX[i];
        int newY = c.y + dirY[i];

        bool currWall = (mazePtr->cellWalls[c.x][c.y] & dir_mask[i]);     // whether current cell has a wall blocking
        bool neighborWall = (mazePtr->cellWalls[newX][newY] & ndir_mask[i]);       // whether neighbor cell has a wall blocking

        //checking if the coordinate is blocked or not
        if (newX >= 0 && newX < 16 && newY >= 0 && newY < 16) { //if cell is in the maze boundaries (need to test if this works)
            if (!currWall && !neighborWall){  // if new cell is blocked by a wall
                list->cells[list->size].pos.x = newX;
                list->cells[list->size].pos.y = newY; //then finally add to the cell list
                list->size++; //increment cell list size

                //std::cerr << "valid cell: (" << newX << "," << newY << ")" << std::endl;
            }
        }
    }
    return list;
}

Coord getBestGoalCell(Maze* mazePtr, Mouse* mousePtr) {
    Coord best_cell_coord;  // return object
    Coord current_coord = mousePtr->mousePos;
    CellList* neighbors = getNeighborCells(mazePtr, current_coord);     // grab neighbors not blocked by walls

    int desired_cell_cost = mazePtr->distances[current_coord.x][current_coord.y] - 1;
    std::cerr << "current cell: (" << current_coord.x << "," << current_coord.y << ")" << std::endl;

    for (int i = 0; i < neighbors->size; i++) {     // iterate through the neighbors
        Coord test_cell_coord = neighbors->cells[i].pos;
        int test_cell_cost = mazePtr->distances[test_cell_coord.x][test_cell_coord.y];

        std::cerr << "valid cell: (" << test_cell_coord.x << "," << test_cell_coord.y << ")" << " cost:" << test_cell_cost << std::endl;

        if (test_cell_cost == desired_cell_cost)   // if the cost is 1 less than the current one
            best_cell_coord = test_cell_coord;
    }
    return best_cell_coord;
}

Coord getBestStartCell(Maze* mazePtr, Mouse* mousePtr) {
    Coord best_cell_coord;  // return object
    Coord current_coord = mousePtr->mousePos;
    CellList* neighbors = getNeighborCells(mazePtr, current_coord);     // grab neighbors not blocked by walls

    int desired_cell_cost = mazePtr->distances[current_coord.x][current_coord.y] + 1;
    std::cerr << "current cell: (" << current_coord.x << "," << current_coord.y << ")" << std::endl;

    for (int i = 0; i < neighbors->size; i++) {     // iterate through the neighbors
        Coord test_cell_coord = neighbors->cells[i].pos;
        int test_cell_cost = mazePtr->distances[test_cell_coord.x][test_cell_coord.y];

        std::cerr << "valid cell: (" << test_cell_coord.x << "," << test_cell_coord.y << ")" << " cost:" << test_cell_cost << std::endl;

        if (test_cell_cost == desired_cell_cost)   // if the cost is 1 less than the current one
            best_cell_coord = test_cell_coord;
    }
    return best_cell_coord;
}

Coord chooseRandomCell(Maze* mazePtr, Mouse* mousePtr) {
    Coord random_cell_coord;  // return object
    Coord current_coord = mousePtr->mousePos;
    CellList* neighbors = getNeighborCells(mazePtr, current_coord);     // grab neighbors not blocked by walls

    random_cell_coord = neighbors->cells[0].pos;

    return random_cell_coord;
}

int countOnes(unsigned int n) { // counts how many ones are in a binary number
    int count = 0;
    while (n) {
        count += n & 1;
        n = n >> 1;
    } 
    return count;
}


void deadEndID(Maze* mazePtr, Mouse* mousePtr) {    // checks if current cell is a dead end
    Coord curPos = mousePtr->mousePos;
    int curCellWalls = mazePtr->cellWalls[mousePtr->mousePos.x][mousePtr->mousePos.y]; 

    //checking for a dead end (which always has 3 walls)
    if (countOnes(curCellWalls) == 3) {
        API::setColor(mousePtr->mousePos.x, mousePtr->mousePos.y, 'Y'); // visually show it is a dead end
        mousePtr->isInDeadEnd = true;   // store in mouse whether we are in a dead end
    }
}

void wallIntersectionTest(Maze* mazePtr, Mouse* mousePtr) {     // sets wall if we are at the mouth of the dead end
    Coord curPos = mousePtr->mousePos;
    int curCellWall = mazePtr->cellWalls[mousePtr->mousePos.x][mousePtr->mousePos.y]; 

    //if dead end is true we know we are returning from a dead end
    if (countOnes(curCellWall) <= 1) { //if mouse is in the intersection
        //set a wall behind the mouse in the current cell
        Coord prevPos = mousePtr->mousePos;
        switch (mousePtr->mouseDir) {
            case NORTH:
                prevPos.y -= 1;
                curCellWall |= SOUTH_MASK;
                API::setWall(curPos.x, curPos.y, 's');
                break;
            case EAST:
                prevPos.x += 1;
                curCellWall |= WEST_MASK;
                API::setWall(curPos.x, curPos.y, 'w');
                break;
            case SOUTH:
                prevPos.y += 1;
                curCellWall |= NORTH_MASK;
                API::setWall(curPos.x, curPos.y, 'n');
                break;
            case WEST:
                prevPos.x -= 1; 
                curCellWall |= EAST_MASK;
                API::setWall(curPos.x, curPos.y, 'e');
                break;
        }

        mousePtr->isInDeadEnd = false;
    }
}

void deadEndCheck (Maze* mazePtr, Mouse* mousePtr) {    // blocks off dead ends with a wall so the mouse will not go there again 
    Coord curPos = mousePtr->mousePos;
    if (!((curPos.x == 0 && curPos.y == 0))) { //check if we are in starting cell
        if (mousePtr->isInDeadEnd) {     // if in dead end, check if we are at the end of it
            wallIntersectionTest(mazePtr, mousePtr);
        }
        else {
            deadEndID(mazePtr, mousePtr); // otherwise, check if we're in a dead end
        }   
    } else { //impossible for deadend to be in starting cell
        mousePtr->isInDeadEnd = false;
    }
}

    int goToPos(int goalIsCenter, Maze* myMaze, Mouse* myMouse){
        while (true) {
            if (goalIsCenter){
                setGoalCenter(myMouse, myMaze);
            }
            scanWalls(myMaze, myMouse);
            deadEndCheck(myMaze, myMouse);
            updateSim(myMaze, myMouse);
            floodFill(myMaze);

            Coord bestCell = getBestGoalCell(myMaze, myMouse);

            move(myMaze, myMouse, &bestCell);
            updateMousePos(myMouse);
            updateSim(myMaze, myMouse);

            if (myMouse->mousePos.x == myMaze->goalPos.x && myMouse->mousePos.y == myMaze->goalPos.y) {
                std::cerr << "it is finished" << std::endl;
                break;
            }
        }
    return 0;
}
#endif
