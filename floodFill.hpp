#ifndef FLOOD
#define FLOOD
#define MAX_COST 255

#include <iostream>
#include <string>

#include "definitions.hpp"
#include "mouseFunctions.hpp"
#include "mazeFunctions.hpp"
#include "testFunctions.hpp"
#include "log.hpp"

void floodFill (Maze* mazePtr){
    //(makes manhattan distances redundant lol)
    Queue q;
    q.head = 0;
    q.tail = 0;
    Cell a;

    for (int x = 0; x < 16; x++) {
        for (int y = 0; y < 16; y++) { 
            if ((x == 8 || x == 7) && (y == 8 || y == 7)) {
                //initialize goal cell distances to 0
                mazePtr->distances[x][y] = 0;
                //add goal coords to the queue first
                a.pos.x = x;
                a.pos.y = y;
                q.kew[q.tail] = a;
                q.tail++;
            } else {
                //initialize all other cells to max distance (255)
                mazePtr->distances[x][y] = MAX_COST;
            }
        }
    }

    while (q.tail - q.head > 0) {
        Cell cur_pos = q.kew[q.head];
        q.head++;
        int newCost = mazePtr->distances[cur_pos.pos.x][cur_pos.pos.y];

        CellList* neighborCells = getNeighborCells(mazePtr, cur_pos.pos);

        for (int i = 0; i < sizeof(neighborCells->cells); i++) {
            if (mazePtr->distances[neighborCells->cells[i].pos.x][neighborCells->cells[i].pos.y] > newCost) {
                mazePtr->distances[neighborCells->cells[i].pos.x][neighborCells->cells[i].pos.y] = newCost;
                q.kew[q.tail] = neighborCells->cells[i];
                q.tail++;
            }
        }
    }
}

/*cell is not blocked from the cell south of it by the north wall ||
cell is not blocked from the cell west of it by the east wall ||
cell is not blocked from the cell north of it by the south wall ||
cell is not blocked from the cell east of it by the west wall*/

#endif