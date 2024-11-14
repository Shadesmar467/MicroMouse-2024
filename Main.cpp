#include <iostream>
#include <string>

//given
#include "API.h"
#include "log.hpp"
//definitions
#include "definitions.hpp"
//test functions
#include "testFunctions.hpp"
//mouse processing
#include "mouseFunctions.hpp"
//maze processing
#include "mazeFunctions.hpp"
//utility functions
#include "utilityFunctions.hpp"
//floodfill
#include "floodFill.hpp"

int main(int argc, char* argv[]) {
    Mouse myMouse;
    Maze myMaze;

    initializeEverything(&myMaze, &myMouse); //hard-code the boundary walls

    API::setColor(0, 0, 'G');
    API::setText(0, 0, "abc");
    scanWalls(&myMaze, &myMouse);
    updateSim(&myMaze, &myMouse);

   while (true) {
        std::cerr << "current mouse position coords: (" << myMouse.mousePos.x << "," << myMouse.mousePos.y << ")";
        setGoalPos(&myMouse, &myMaze);
        floodFill(&myMaze);
        scanWalls(&myMaze, &myMouse);
        updateSim(&myMaze, &myMouse);
     
        Coord bestCell = getBestCell(&myMaze, &myMouse);
        move(&myMaze, &myMouse, bestCell);

        updateMousePos(&myMouse);
        
        if ((myMouse.mousePos.x == 7 || myMouse.mousePos.x == 8) && (myMouse.mousePos.y == 7 || myMouse.mousePos.x == 8)) {
            break;
        }
    }
}