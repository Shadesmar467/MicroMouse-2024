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
    Mouse myMouse = {0};
    Maze myMaze = {0};

    //initializing manhattan distances, cell walls, and goal pos
    setManDist(&myMaze);
    initialWalls();

    API::setColor(0, 0, 'G');
    API::setText(0, 0, "abc");
    scanWalls(&myMaze, &myMouse);
    updateSim(&myMaze, &myMouse);

   while (true) {
        if (!API::wallLeft()) {
            API::turnLeft();
            myMouse.mouseDir = mTurnLeft(&myMouse);
            directionCheck(&myMouse);
        }
        while (API::wallFront()) {
            API::turnRight();
            myMouse.mouseDir = mTurnRight(&myMouse);
            directionCheck(&myMouse);
        }
        API::moveForward();
        updateMousePos(&myMouse);
        setGoalPos(&myMouse, &myMaze);
        scanWalls(&myMaze, &myMouse);
        updateSim(&myMaze, &myMouse);
        floodFill(&myMaze);
        getBestCell(&myMaze, &myMouse);
        
    }
}