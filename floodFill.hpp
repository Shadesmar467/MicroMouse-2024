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

void floodFill (Maze* mazePtr, Queue* qPtr){
    //initialize maze distances all to 255 (except goal cells which are 0) 
    //(makes manhattan distances redundant lol)
    for (int x = 0; x < 16; x++) {
        for (int y = 0; y < 16; y++) { 
            if ((x == 8 || x == 7) && (y == 8 || y == 7)) {
                mazePtr->distances[x][y] = 0;
            } else {
                mazePtr->distances[x][y] = MAX_COST;
            }
        }
    }

    qPtr->head = 0;
    qPtr->tail = 0;



    

}

#endif