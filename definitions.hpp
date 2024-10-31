#ifndef DEF
#define DEF

    // direction
    char dir_chars[4] = {'n', 'e', 's', 'w'};

    struct Coord {
        int x;
        int y;
    };

    enum Direction {
        NORTH,
        EAST,
        SOUTH,
        WEST
    };

    enum dirBitmask {
        NORTH_MASK = 0b1000,
        EAST_MASK  = 0b0100,
        SOUTH_MASK = 0b0010,
        WEST_MASK  = 0b0001
    };

    struct Mouse {
        Coord mousePos;
        Direction mouseDir = NORTH;
    };

    typedef struct {
       Coord goalPos;
       int cellWalls[16][16];
       int distances[16][16];
    } Maze;


#endif