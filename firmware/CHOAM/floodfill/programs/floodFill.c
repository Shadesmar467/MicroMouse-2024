#include "floodfill.h"
#include "definitions.h"
#include "mouseFunctions.h"
#include "mazeFunctions.h"
#include "utilityFunctions.h"

void floodFill (Maze* mazePtr) {
    Queue q;
    q.head = 0;
    q.tail = 0;
    Cell a;

    char distConvert[2];

    // floodfill setup
    for (int x = 0; x < 16; x++) {
        for (int y = 0; y < 16; y++) {
            if (x == mazePtr->goalPos.x && y == mazePtr->goalPos.y) {     //initialize goal cells

                mazePtr->distances[x][y] = 0;   //set distances to 0

                a.pos.x = x;                    //add goal cells to the queue
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
    while (q.head < q.tail) {
        Cell cur_cell = q.kew[q.head];  // pop first item from queue
        q.head++;
        CellList* neighborList = getNeighborCells(mazePtr, cur_cell.pos);   // get neighboring cells that arent blocked by walls
        int new_cost = mazePtr->distances[cur_cell.pos.x][cur_cell.pos.y] + 1;  // cost of neighboring cells will be current cell cost + 1

        for (int i = 0; i < neighborList->size; i++) {  // setting neighbors cost and pushing to queue
            Cell cur_neighbor = neighborList->cells[i];
            int cur_neighbor_cost = mazePtr->distances[cur_neighbor.pos.x][cur_neighbor.pos.y];

            if (cur_neighbor_cost > new_cost){  // only set to new cost if old cost was greater
                q.kew[q.tail] = cur_neighbor;
                q.tail++;
                mazePtr->distances[cur_neighbor.pos.x][cur_neighbor.pos.y] = new_cost;
                sprintf(distConvert, "%d", new_cost);
                API::setText(cur_neighbor.pos.x, cur_neighbor.pos.y, distConvert);
            }
        }
    }
}
