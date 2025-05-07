//definitions
#include "definitions.h"
#include "mouseFunctions.h"
#include "mazeFunctions.h"
#include "utilityFunctions.h"
#include "floodFill.h"

int main(int argc, char* argv[]) {
    Mouse myMouse;
    Maze myMaze;

    initializeEverything(&myMaze, &myMouse); //hard-code the boundary walls

    setGoalPos({15,15}, &myMaze);
    goToPos(0, &myMaze, &myMouse);

    setGoalPos({0,15}, &myMaze);
    goToPos(0, &myMaze, &myMouse);

    goToPos(1, &myMaze, &myMouse);

    setGoalPos({0,0}, &myMaze);
    goToPos(0, &myMaze, &myMouse);

    goToPos(1, &myMaze, &myMouse);

    return 0;
}
