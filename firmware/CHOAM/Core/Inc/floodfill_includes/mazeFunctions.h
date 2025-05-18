/*
 * maze_functions.h
 *
 *  Created on: May 17, 2025
 *      Author: adamhwu
 */

#ifndef INC_FLOODFILL_INCLUDES_MAZEFUNCTIONS_H_
#define INC_FLOODFILL_INCLUDES_MAZEFUNCTIONS_H_

void init_maze(Maze* maze, Mouse* mouse);

void scan_walls(Maze* maze, Mouse* mouse);

void update_sim(Maze* maze, Mouse* mouse);

void setGoalCenter(Mouse* mouse, Maze* maze);

void setGoalPos(Coord coord, Maze* maze);

#endif /* INC_FLOODFILL_INCLUDES_MAZEFUNCTIONS_H_ */
