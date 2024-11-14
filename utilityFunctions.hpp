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
            q->kew[x] = {0};
    }
}

CellList* getNeighborCells(Maze* mazePtr, Coord c) { //input a coordinate C, get back neighbors
    
    CellList* list = (CellList*)malloc(sizeof(CellList));
    //this is a cell list named list allocating memory for all cells in the list

    int dirX[] = {0, -1, 0, 1};
    int dirY[] = {-1, 0, 1, 0};
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

        //sprintf(test, "%d", mazePtr->cellWalls[newX][newY]);
        //log(test);

        //checking if the coordinate is blocked or not
        if (newX >= 0 && newX < 16 && newY >= 0 && newY < 16) { //if cell is in the maze boundaries (need to test if this works)
            if ((mazePtr->cellWalls[newX][newY] & dir_mask[i])) {
            continue;
            }
            list->cells[list->size].pos.x = newX;
            list->cells[list->size].pos.y = newY; //then finally add to the cell list
            list->size++; //increment cell list size
        }
    }
    return list;
}

Coord getBestCell(Maze* mazePtr, Coord current_cell) {
    Coord best_cell;
    int dirX[] = {0, -1, 0, 1};
    int dirY[] = {-1, 0, 1, 0};



    for (int i = 0; i < 4; i++) {
        int newX = current_cell.x + dirX[i];
        int newY = current_cell.y + dirY[i];

        int test_cell_cost = mazePtr->distances[newX][newY];
        int desired_cell_cost = mazePtr->distances[current_cell.x][current_cell.y] - 1;
        if (test_cell_cost == desired_cell_cost){
            best_cell.x = newX;
            best_cell.y = newY;
        }
    }
    return best_cell;
}

#endif