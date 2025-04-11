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

int goToPos(int goalIsCenter, Maze* myMaze, Mouse* myMouse){
    while (true) {
        if (goalIsCenter){
            setGoalCenter(myMouse, myMaze);
        }
        scanWalls(myMaze, myMouse);
        deadEndCheck(myMaze, myMouse);
        updateSim(myMaze, myMouse);
        floodFill(myMaze);

        Coord bestCell = getBestGoalCell(myMaze, myMouse);

        move(myMaze, myMouse, &bestCell);
        updateMousePos(myMouse);
        updateSim(myMaze, myMouse);

        if (myMouse->mousePos.x == myMaze->goalPos.x && myMouse->mousePos.y == myMaze->goalPos.y) {
            std::cerr << "it is finished" << std::endl;
            break;
        }
    }
    return 0;
}

int main(int argc, char* argv[]) {
    Mouse myMouse;
    Maze myMaze;

    initializeEverything(&myMaze, &myMouse); //hard-code the boundary walls
    //initTestMaze(&myMaze, &myMouse);
    updateSim(&myMaze, &myMouse);

    setGoalPos({15,15}, &myMaze);
    goToPos(0, &myMaze, &myMouse);

    setGoalPos({0,15}, &myMaze);
    goToPos(0, &myMaze, &myMouse);

    goToPos(1, &myMaze, &myMouse);

    setGoalPos({0,0}, &myMaze);
    goToPos(0, &myMaze, &myMouse);

    goToPos(1, &myMaze, &myMouse);

    API::setColor(0, 0, 'G');
    API::setText(0, 0, "abc");

    return 0;
}
