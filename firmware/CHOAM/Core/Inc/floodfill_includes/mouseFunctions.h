#ifndef INC_FLOODFILL_INCLUDES_MOUSEFUNCTIONS_H_
#define INC_FLOODFILL_INCLUDES_MOUSEFUNCTIONS_H_

#include "definitions.h"

void updateMousePos(Mouse* mouse);

void move(Maze* maze, Mouse* mouse, Coord* bestCell);

#endif /* INC_FLOODFILL_INCLUDES_MOUSEFUNCTIONS_H_ */
