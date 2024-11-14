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
    int testWhile = 10;

    for (int x = 0; x < 16; x++) {
        for (int y = 0; y < 16; y++) { 
            if ((x == 8 || x == 7) && (y == 8 || y == 7)) {
                //initialize goal cell distances to 0
                mazePtr->distances[x][y] = 0;
                //print distance to screen
                sprintf(distConvert, "%d", mazePtr->distances[x][y]);
                API::setText(x, y, distConvert);
                //add goal cells to the queue first
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
        int newCost = (mazePtr->distances[cur_pos.pos.x][cur_pos.pos.y]) + 1;
        CellList* neighborCells = getNeighborCells(mazePtr, cur_pos.pos);

        for (int i = 0; i < sizeof(neighborCells->cells); i++) {
            Cell cur_cell = neighborCells->cells[i];
            int cur_cell_distance = mazePtr->distances[cur_cell.pos.x][cur_cell.pos.y];
            int cur_pos_distance = mazePtr->distances[cur_pos.pos.x][cur_pos.pos.y];

            if (cur_cell_distance > newCost) {
                cur_cell_distance = newCost;
                sprintf(distConvert, "%d", cur_cell_distance);
                API::setText(cur_cell.pos.x, cur_cell.pos.y, distConvert);
                q.kew[q.tail] = cur_cell;
                q.tail++;
            }
        }
        testWhile--;
    }
}

#endif