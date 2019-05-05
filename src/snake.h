#ifndef SNAKE_H_
#define SNAKE_H_

#include "log.h"
#include "engine.h"

#include <deque>
#include <ncurses.h>

#define NX_SNAKE_BODY ACS_BOARD 
#define NX_SNAKE_CLS ' '

#define NX_SNAKE_START_SIZE 5
#define NX_SNAKE_START_X 5
#define NX_SNAKE_START_Y 5

typedef struct _STSnakeBody {
    int x; ///< Position in column of snake body node.
    int y; ///< Position in line of snake body node.
    bool isHead;
    bool isLastRemovedNode; ///< Mark the node to be deleted in the next render.   
} STSnakeBody;

class cSnake {

public: 
    cSnake();

    ~cSnake();

    bool initialize(const int iMaxSize,
                    const int iSize = NX_SNAKE_START_SIZE);

    bool setSize(const int iSize);    

    int getSize();

    void setMaxSize(const int iMaxSize);

    int getMaxSize();

    bool increaseSize(const int iSize = 1);    

    void render();

    void create(const int x, 
                const int y,                     
                eNXKeyPressed eNXDirection);

    void setDirection(eNXKeyPressed eNXMovDir);

    eNXKeyPressed getDirection();

    STSnakeBody getHeadPosition();

    void move(eNXKeyPressed eNXMovDir);

    bool checkSnakeBodyCollision();

    void logSnakeNodes();

private:
    bool m_bIsFirstRender;
    bool m_bWasCalledIncrease;
    int m_iSize;
    int m_iMaxSize;    
    std::deque<STSnakeBody> m_odqSnakeNodes;    
    eNXKeyPressed m_eSnakeDirection;
    STSnakeBody oRemovedSnakeNode;

};

#endif // SNAKE_H_
