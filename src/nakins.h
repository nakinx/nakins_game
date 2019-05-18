#ifndef NAKINS_H_
#define NAKINS_H_

#include <ncurses.h>

#define NX_WALL ACS_CKBOARD
#define NX_SNAKE_FOOD ACS_BOARD 
#define NX_EMPTY ' '

#define NX_X COLS
#define NX_Y LINES

#define NX_MIN_X 90
#define NX_MIN_Y 22

#define NX_KEY_ENTER 10

enum class eNXKeyPressed {
    up = 1,
    down = 2,
    left = 4,
    right = 8,
    escape = 16,
    enter = 32,
    undefined = 2048,
};

enum class eNXOption {
    yes = 1,
    no = 2,
};

#endif //NAKINS_H_