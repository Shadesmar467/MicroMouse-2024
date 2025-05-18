#include "floodfill_includes/definitions.h"

// direction
char dir_chars[4] = {'n', 'e', 's', 'w'};

//direction bitmask for floodfill
int dir_mask[4] = {0b1000, 0b0100, 0b0010, 0b0001};
int ndir_mask[4] = {0b0010, 0b0001, 0b1000, 0b0100};
