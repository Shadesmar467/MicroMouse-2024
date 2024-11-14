#ifndef FLOOD
#define FLOOD
#define MAX_COST 255

#include <iostream>
#include <string>
#include <stdio.h>

#include "definitions.hpp"
#include "mouseFunctions.hpp"
#include "mazeFunctions.hpp"
#include "testFunctions.hpp"
#include "utilityFunctions.hpp"
#include "log.hpp"

void floodFill (Maze* mazePtr){
    //(makes manhattan distances redundant lol)
    Queue q;
    q.head = 0;
    q.tail = 0;
    Cell a;
    char distConvert[2];

    for (int x = 0; x < 16; x++) {
        for (int y = 0; y < 16; y++) { 
            if ((x == 8 || x == 7) && (y == 8 || y == 7)) {
                //initialize goal cell distances to 0
                mazePtr->distances[x][y] = 0;
                //print distance to screen
                sprintf(distConvert, "%d", mazePtr->distances[x][y]);
                API::setText(x, y, distConvert);
                //add goal coords to the queue first
                a.pos.x = x;
                a.pos.y = y;
                q.kew[q.tail] = a;
                q.tail++;
            } else {
                //initialize all other cells to max distance (255)
                mazePtr->distances[x][y] = MAX_COST;
                sprintf(distConvert, "%d", mazePtr->distances[x][y]);
                API::setText(x, y, distConvert);
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
                sprintf(distConvert, "%d", mazePtr->distances[neighborCells->cells[i].pos.x][neighborCells->cells[i].pos.y]);
                API::setText(cur_pos.pos.x, cur_pos.pos.y, distConvert);
                q.kew[q.tail] = neighborCells->cells[i];
                q.tail++;
            }
        }
    }
}

#endif