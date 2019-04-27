#ifndef MAP_H_
#define MAP_H_

#include <ncurses.h>

#define NX_WALL ACS_CKBOARD
#define NX_SNAKE_FOOD ACS_DIAMOND 

typedef struct _STMapWall {

    int x;
    int y;
    int type;

} STMapWall;

typedef struct _STSnakeFood {

    int x;
    int y;
    int type;

} STSnakeFood;

class cMap {

public:
    cMap();

    ~cMap();

    bool initialize(const int iChosenMap);

    int getEmptySpaceSize();

    bool load();

    void render();

    void createSnakeFood();

    STSnakeFood getSnakeFoodPosition();

private:
    bool m_bIsDefaultMap;
    int m_iEmptySpaceSize;    
    STSnakeFood m_stSnakeFood;

    void calculateEmptySpaceSize();

    bool checkResolution();

    unsigned int randomIntegerNumber(const unsigned int iMin,
                                     const unsigned int iMax);

};

#endif // MAP_H_