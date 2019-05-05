#ifndef MAP_H_
#define MAP_H_

#include "nakins.h"

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

    void renderSnakeFood();

    STSnakeFood getSnakeFoodPosition();

    void clearSnakeFoodPosition();

private:
    bool m_bIsDefaultMap;
    int m_iEmptySpaceSize;    
    int m_uiX; ///< Columns.
    int m_uiY; ///< Lines.
    STSnakeFood m_stSnakeFood;

    void calculateEmptySpaceSize();

    bool checkResolution();

    unsigned int randomIntegerNumber(const unsigned int iMin,
                                     const unsigned int iMax);

};

#endif // MAP_H_