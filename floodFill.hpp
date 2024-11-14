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
    Queue q;
    q.head = 0;
    q.tail = 0;
    Cell a;
    char distConvert[2];
    char testx[20];
    char testy[20];
    char dout[20];
    char num[20];

    for (int x = 0; x < 16; x++) {
        for (int y = 0; y < 16; y++) { 
            if ((x == 8 || x == 7) && (y == 8 || y == 7)) {
                //initialize goal cell distances to 0
                mazePtr->distances[x][y] = 0;
                //print distance to screen
                
                //add goal cells to the queue first
                a.pos.x = x;
                a.pos.y = y;
                q.kew[q.tail] = a;
                q.tail++;
            } else {
                //initialize all other cells to max distance (255)
                mazePtr->distances[x][y] = MAX_COST;
            }
            sprintf(distConvert, "%d", mazePtr->distances[x][y]);
            API::setText(x, y, distConvert);
        }
    }
    int instruction = 0;
    while (q.head < q.tail) {
        Cell cur_cell = q.kew[q.head];  // pop first item from queue
        q.head++;
        CellList* neighborList = getNeighborCells(mazePtr, cur_cell.pos);   // get neighboring cells that arent blocked by walls
        int new_cost = mazePtr->distances[cur_cell.pos.x][cur_cell.pos.y] + 1;  // cost of neighboring cells is current cell cost + 1

        sprintf(testx, "%d", cur_cell.pos.x);
        sprintf(testy, "%d", cur_cell.pos.y);
        sprintf(dout, "%d", neighborList->size);
        log("current cell x and y: ");
        log(testx);
        log(testy);
        log("size of neighborList: ");
        log(dout);

        for (int i = 0; i < neighborList->size; i++) {
            instruction++;
            Cell cur_neighbor = neighborList->cells[i];
            int cur_neighbor_cost = mazePtr->distances[cur_neighbor.pos.x][cur_neighbor.pos.y];
            sprintf(testx, "%d", cur_neighbor.pos.x);
            sprintf(testy, "%d", cur_neighbor.pos.y);
            sprintf(dout, "%d", cur_neighbor_cost);
            sprintf(num, "%d", q.tail);
            log("x and y, old cost, q.tail: ");
            log(testx);
            log(testy);
            log(dout);
            log(num);
            if (cur_neighbor_cost > new_cost){
                q.kew[q.tail] = cur_neighbor;
                q.tail++;
                mazePtr->distances[cur_neighbor.pos.x][cur_neighbor.pos.y] = new_cost;
                sprintf(distConvert, "%d", new_cost);
                API::setText(cur_neighbor.pos.x, cur_neighbor.pos.y, distConvert);
            }
        }
    }
    
}

#endif