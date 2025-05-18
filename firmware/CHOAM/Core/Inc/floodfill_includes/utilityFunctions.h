/*
 * utilityFunctions.h
 *
 *  Created on: May 17, 2025
 *      Author: adamhwu, JERMEMREMREIAH
 */

#ifndef INC_FLOODFILL_INCLUDES_UTILITYFUNCTIONS_H_
#define INC_FLOODFILL_INCLUDES_UTILITYFUNCTIONS_H_

#include "definitions.h"

void initQ(Queue* q);

CellList* getNeighborCells(Maze* mazePtr, Coord c);

Coord getBestGoalCell(Maze* mazePtr, Mouse* mousePtr);

Coord getBestStartCell(Maze* mazePtr, Mouse* mousePtr);

Coord chooseRandomCell(Maze* mazePtr, Mouse* mousePtr);

int countOnes(unsigned int n);

void deadEndID(Maze* mazePtr, Mouse* mousePtr);

void wallIntersectionTest(Maze* mazePtr, Mouse* mousePtr);

void deadEndCheck (Maze* mazePtr, Mouse* mousePtr);

int goToPos(int goalIsCenter, Maze* myMaze, Mouse* myMouse);

#endif /* INC_FLOODFILL_INCLUDES_UTILITYFUNCTIONS_H_ */
