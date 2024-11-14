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

        //sprintf(test, "%d", mazePtr->cellWalls[newX][newY]);
        //log(test);

        //checking if the coordinate is blocked or not
        if (newX >= 0 && newX < 16 && newY >= 0 && newY < 16) { //if cell is in the maze boundaries (need to test if this works)
            if (!(mazePtr->cellWalls[c.x][c.y] & dir_mask[i])) {  // if new cell is blocked by a wall
                list->cells[list->size].pos.x = newX;
                list->cells[list->size].pos.y = newY; //then finally add to the cell list
                list->size++; //increment cell list size
            }
        }
    }
    return list;
}

Coord getBestCell(Maze* mazePtr, Mouse* mousePtr) {
    Coord best_cell_coord;  // return object with coords of best cell
    Coord current_coord = mousePtr->mousePos;   // current coords of mouse
    CellList* neighbors = getNeighborCells(mazePtr, current_coord);     // calculate neighbors not blocked by walls

    char curCellx[20];
    char curCelly[20];
    char testx[20];
    char testy[20];


    for (int i = 0; i < neighbors->size; i++) {
        Coord test_cell_coord = neighbors->cells[i].pos;

        /*sprintf(testx, "%d", test_cell_coord.x);
        sprintf(testy, "%d", test_cell_coord.y);
        sprintf(curCellx, "%d", mazePtr->cellWalls[current_coord.x][current_coord.y]);
        log("current cellWall");
        log(curCellx);
        log("testcell options: ");
        log(testx);
        log(testy);*/


        int test_cell_cost = mazePtr->distances[test_cell_coord.x][test_cell_coord.y];
        int desired_cell_cost = mazePtr->distances[current_coord.x][current_coord.y] - 1;

        if (test_cell_cost == desired_cell_cost){
            best_cell_coord = test_cell_coord;
        }
    }
    /*sprintf(curCellx, "%d", current_coord.x);
    sprintf(curCelly, "%d", current_coord.y);
    sprintf(testx, "%d", best_cell_coord.x);
    sprintf(testy, "%d", best_cell_coord.y);
    log("currently: ");
    log(curCellx);
    log(curCelly);
    log("x and y of best cell: ");
    log(testx);
    log(testy);*/
    
    return best_cell_coord;
}

#endif