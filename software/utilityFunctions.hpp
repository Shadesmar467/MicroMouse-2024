#ifndef UTIL
#define UTIL

#include <iostream>
#include <string>
#include <stdbool.h>

#include "stdlib.h"

#include "API.h"
#include "definitions.hpp"
#include "log.hpp"

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

Coord getBestCell(Maze* mazePtr, Mouse* mousePtr) {
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

int countOnes(unsigned int n) {
    int count = 0;
    while (n) {
        count += n & 1;
        n = n >> 1;
    } 
    return count;
}


void deadEndID(Maze* mazePtr, Mouse* mousePtr, bool* in) {
    Coord curPos = mousePtr->mousePos;
    int curCellWall = mazePtr->cellWalls[mousePtr->mousePos.x][mousePtr->mousePos.y]; 

    //checking for a dead end
    if ((mousePtr->mouseDir == SOUTH && curCellWall == 0b1101) ||
        (mousePtr->mouseDir == NORTH && curCellWall == 0b0111) ||
        (mousePtr->mouseDir == EAST && curCellWall == 0b1011) ||
        (mousePtr->mouseDir == WEST && curCellWall == 0b1110)) {
        API::setColor(mousePtr->mousePos.x, mousePtr->mousePos.y, 'Y');
        *in = true;
    }
}

void wallIntersectionTest(Maze* mazePtr, Mouse* mousePtr, bool* in) {

    Coord curPos = mousePtr->mousePos;
    int curCellWall = mazePtr->cellWalls[mousePtr->mousePos.x][mousePtr->mousePos.y]; 

    //if dead end is true we know we are returning from a dead end
    //and if there is only one wall in the cell...
    if ((countOnes(curCellWall) <= 1) && (*in == true)) {

        //set a wall behind the mouse in the current cell
        if (mousePtr->mouseDir == SOUTH) {
            API::setColor(mousePtr->mousePos.x, mousePtr->mousePos.y, 'R');
            curCellWall |= NORTH_MASK;
            API::setWall(curPos.x, curPos.y, 's');
            *in = false;
        }
        if (mousePtr->mouseDir == NORTH) {
            API::setColor(mousePtr->mousePos.x, mousePtr->mousePos.y, 'R');
            curCellWall |= SOUTH_MASK;
            API::setWall(curPos.x, curPos.y, 'n');
            *in = false;
        } 
        if (mousePtr->mouseDir == EAST) {
            API::setColor(mousePtr->mousePos.x, mousePtr->mousePos.y, 'R');
            curCellWall |= WEST_MASK;
            API::setWall(curPos.x, curPos.y, 'e');
            *in = false;
        }
        if (mousePtr->mouseDir == WEST) {
            API::setColor(mousePtr->mousePos.x, mousePtr->mousePos.y, 'R');
            curCellWall |= EAST_MASK;
            API::setWall(curPos.x, curPos.y, 'w');
            *in = false;
        }
    }
}

void deadEndCheck (Maze* mazePtr, Mouse* mousePtr) {
    static bool deadEnd;
    deadEndID(mazePtr, mousePtr, &deadEnd);
    wallIntersectionTest(mazePtr, mousePtr, &deadEnd);
}

#endif