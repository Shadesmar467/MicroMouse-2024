/*
 * definitions.h
 *
 *  Created on: May 17, 2025
 *      Author: adamhwu
 */

#ifndef INC_DEFINITIONS_H_
#define INC_DEFINITIONS_H_

#include <stdbool.h>

#define goal1 (Coord){15, 15}
#define goal2 (Coord){0, 15}
#define initialCoord (Coord){0, 0}

    // direction
    char dir_chars[4] = {'n', 'e', 's', 'w'};

    //direction bitmask for floodfill
    int dir_mask[4] = {0b1000, 0b0100, 0b0010, 0b0001};
    int ndir_mask[4] = {0b0010, 0b0001, 0b1000, 0b0100};

    typedef struct {
        int x;
        int y;
    } Coord;

    typedef enum {
        NORTH,
        EAST,
        SOUTH,
        WEST
    } Direction;

    typedef enum {
        NORTH_MASK = 0b1000,
        EAST_MASK  = 0b0100,
        SOUTH_MASK = 0b0010,
        WEST_MASK  = 0b0001
    } dirBitmask;

    typedef struct {
        Coord pos;
        Direction dir;
    } Cell;

    typedef struct {
        int size;
        Cell* cells; //array of cells
    } CellList;

    typedef struct  {
        Coord mousePos;
        Direction mouseDir;
        bool isInDeadEnd;
    } Mouse;

    typedef struct {
       Coord goalPos;
       int cellWalls[16][16];
       int distances[16][16];
    } Maze;

    typedef struct {
        Cell kew[256];
        int head;
        int tail;
    } Queue;

#endif /* INC_DEFINITIONS_H_ */
