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

    // floodfill setup
    for (int x = 0; x < 16; x++) {
        for (int y = 0; y < 16; y++) { 
            if ((x == 8 || x == 7) && (y == 8 || y == 7)) {     //initialize goal cell distances to 0
                
                mazePtr->distances[x][y] = 0;   //print distance to screen

                a.pos.x = x;                    //add goal cells to the queue first
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

    // floodfill loop
    for (int j = 0; j < 10; j++) {
        Cell cur_cell = q.kew[q.head];  // pop first item from queue
        q.head++;
        CellList* neighborList = getNeighborCells(mazePtr, cur_cell.pos);   // get neighboring cells that arent blocked by walls
        int new_cost = mazePtr->distances[cur_cell.pos.x][cur_cell.pos.y] + 1;  // cost of neighboring cells is current cell cost + 1

        for (int i = 0; i < neighborList->size; i++) {
            Cell cur_neighbor = neighborList->cells[i];
            int cur_neighbor_cost = mazePtr->distances[cur_neighbor.pos.x][cur_neighbor.pos.y];

            //std::cerr << "current position coords: (" << cur_neighbor.pos.x << "," << cur_neighbor.pos.y << ")" <<std::endl;

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