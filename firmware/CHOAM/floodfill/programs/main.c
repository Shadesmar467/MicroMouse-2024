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

    setGoalPos(goal1, &myMaze);
    goToPos(0, &myMaze, &myMouse);

    setGoalPos(goal2, &myMaze);
    goToPos(0, &myMaze, &myMouse);

    goToPos(1, &myMaze, &myMouse);

    setGoalPos(initialCoord, &myMaze);
    goToPos(0, &myMaze, &myMouse);

    goToPos(1, &myMaze, &myMouse);

    return 0;
}
