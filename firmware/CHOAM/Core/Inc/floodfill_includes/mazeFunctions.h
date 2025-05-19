#ifndef INC_FLOODFILL_INCLUDES_MAZEFUNCTIONS_H_
#define INC_FLOODFILL_INCLUDES_MAZEFUNCTIONS_H_

#include "definitions.h"

void init_maze(Maze* maze, Mouse* mouse);

void scan_walls(Maze* maze, Mouse* mouse);

void setGoalCenter(Mouse* mouse, Maze* maze);

void setGoalPos(Coord coord, Maze* maze);

#endif /* INC_FLOODFILL_INCLUDES_MAZEFUNCTIONS_H_ */
