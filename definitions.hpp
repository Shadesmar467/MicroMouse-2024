#ifndef DEF
#define DEF

    // direction
    char dir_chars[4] = {'n', 'e', 's', 'w'};

    //direction bitmask for floodfill
    int dir_mask[4] = {0b1000, 0b0100, 0b0010, 0b0001};

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

    typedef struct {
        Coord pos;
        Direction dir;
    } Cell;

    typedef struct {
        int size;
        Cell* cells; //array of cells
    } CellList;

    struct Mouse {
        Coord mousePos;
        Direction mouseDir;
    };

    typedef struct {
       Coord goalPos;
       int cellWalls[16][16];
       int distances[16][16];
    } Maze;

    typedef struct {
        Cell kew[260];
        int head = 0;
        int tail = 0;
    } Queue;


#endif