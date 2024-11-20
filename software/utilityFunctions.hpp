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
    int dirX[] = {0, 1, 0, -1};     // used to find pos of neighbor cells
    int dirY[] = {1, 0, -1, 0};

    CellList* list = (CellList*)malloc(sizeof(CellList));     //this is a cell list named list allocating memory for all cells in the list
    list->cells = (Cell*)malloc(list->size * sizeof(Cell));
    list->size = 0;

    //now i need to calculate the new coordinates of each cell and store the cell in the array
    for (int i = 0; i < 4; i++) {
        int newX = c.x + dirX[i];
        int newY = c.y + dirY[i];

        // dir_mask checks order of 'nesw', ndir_mask checks order of 'swne' to match orientation of adjacent cell
        bool currWall = (mazePtr->cellWalls[c.x][c.y] & dir_mask[i]);     // true if current cell has a wall between current and neighbor cell
        bool neighborWall = (mazePtr->cellWalls[newX][newY] & ndir_mask[i]);       // true if neighbor cell has a wall current and neighbor cell

        if (newX >= 0 && newX < 16 && newY >= 0 && newY < 16) { //if cell is in the maze boundaries
            if (!currWall && !neighborWall){  // if new cell is not blocked by a wall
                list->cells[list->size].pos.x = newX;
                list->cells[list->size].pos.y = newY; //then finally add to the cell list
                list->size++; //increment cell list size
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

#endif