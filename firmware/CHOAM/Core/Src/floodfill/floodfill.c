#include "floodfill_includes/floodfill.h"
#include "floodfill_includes/utilityFunctions.h"
#include "values.h"
#include <stdlib.h>

void floodFill (Maze* maze) {
    Queue q;
    q.head = 0;
    q.tail = 0;
    Cell a;

    // floodfill setup
    for (int x = 0; x < 16; x++) {
        for (int y = 0; y < 16; y++) {
            if (x == maze->goalPos.x && y == maze->goalPos.y) {     //initialize goal cells

                maze->distances[x][y] = 0;   //set distances to 0

                a.pos.x = x;                    //add goal cells to the queue
                a.pos.y = y;
                q.kew[q.tail] = a;
                q.tail++;
            } else {
                //initialize all other cells to max distance (255)
                maze->distances[x][y] = MAX_COST;
            }
        }
    }

    // floodfill loop
    while (q.head < q.tail) {
        Cell cur_cell = q.kew[q.head];  // pop first item from queue
        q.head++;

        CellList* neighborList = getNeighborCells(maze, cur_cell.pos);   // get neighboring cells that arent blocked by walls
        int new_cost = maze->distances[cur_cell.pos.x][cur_cell.pos.y] + 1;  // cost of neighboring cells will be current cell cost + 1

        for (int i = 0; i < neighborList->size; i++) {  // setting neighbors cost and pushing to queue
            Cell cur_neighbor = neighborList->cells[i];
            int cur_neighbor_cost = maze->distances[cur_neighbor.pos.x][cur_neighbor.pos.y];

            if (cur_neighbor_cost > new_cost){  // only set to new cost if old cost was greater
                q.kew[q.tail] = cur_neighbor;
                q.tail++;
                maze->distances[cur_neighbor.pos.x][cur_neighbor.pos.y] = new_cost;
            }
        }
        free(neighborList->cells);
        free(neighborList);
    }
}
