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

void initTestMaze(Maze* mazePtr, Mouse* mousePtr) {
    Coord c;
    for (int x = 5; x < 11; x++){
        for (int y = 5; y < 11; y++){
            mousePtr->mousePos.x = x;
            mousePtr->mousePos.y = y;
            scanWalls(mazePtr, mousePtr);
        }
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

        //checking if the coordinate is blocked or not
        if (newX >= 0 && newX < 16 && newY >= 0 && newY < 16) { //if cell is in the maze boundaries (need to test if this works)
            if (!(mazePtr->cellWalls[c.x][c.y] & dir_mask[i])) {  // if new cell is blocked by a wall
                list->cells[list->size].pos.x = newX;
                list->cells[list->size].pos.y = newY; //then finally add to the cell list
                list->size++; //increment cell list size

                std::cerr << "valid cell: (" << newX << "," << newY << ")";
            }
        }
    }
    return list;
}

Coord getBestCell(Maze* mazePtr, Mouse* mousePtr) {

    Coord best_cell_coord;  // return object with coords of best cell
    Coord current_coord = mousePtr->mousePos;   // current coords of mouse
    CellList* neighbors = getNeighborCells(mazePtr, current_coord);     // calculate neighbors not blocked by walls

    std::cerr << "current: (" << current_coord.x << "," << current_coord.y << ")" << std::endl;

    for (int i = 0; i < neighbors->size; i++) {
        Coord test_cell_coord = neighbors->cells[i].pos;
        int test_cell_cost = mazePtr->distances[test_cell_coord.x][test_cell_coord.y];
        int desired_cell_cost = mazePtr->distances[current_coord.x][current_coord.y] - 1;

        std::cerr << "valid cell: (" << test_cell_coord.x << "," << test_cell_coord.y << ")" << std::endl;

        if (test_cell_cost == desired_cell_cost){
            best_cell_coord = test_cell_coord;
        }
    }
    return best_cell_coord;
}

#endif