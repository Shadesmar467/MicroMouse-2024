#ifndef UTIL
#define UTIL

#include <iostream>
#include <string>

#include "stdlib.h"

#include "API.h"
#include "definitions.hpp"
#include "log.hpp"

void initQ(Queue* q) {
    for (int x = 0; x < 255; x++) {
            q->cellList[x] = {0};
    }
}

CellList* getNeighborCells(Maze* mazePtr, Coord c) { //input a coordinate C, get back neighbors
    
    CellList* list = (CellList*)malloc(sizeof(CellList));
    //this is a cell list named list allocating memory for all cells in the list

    int dirX[] = {-1, 1, 0, 0};
    int dirY[] = {0, 0, -1, 1};
    int count = 0;  

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

        if (newX >= 0 && newX < 16 && newY >= 0 && newY < 16) { //if cell is in the maze boundaries
            list->cells[list->size].pos.x = newX;
            list->cells[list->size].pos.y = newY;
            list->size++;
        }
    }

    return list;
}

Cell getBestCell() {
    //will need to use dir_mask to check walls i think
    //not dependent on mouse direction
}

#endif