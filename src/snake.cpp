#include "snake.h"

#include <iostream>
#include <sstream>

cSnake::cSnake() 
    : m_bIsFirstRender(true),
      m_iSize(0),
      m_iMaxSize(0) {
}

cSnake::~cSnake() {
}

bool cSnake::initialize(const int iMaxSize,
                        const int iSize) {

    cLog::getInstance().write(eServeriyLevel::Info, "Initializing snake.");
 
    setMaxSize(iMaxSize);

    if (setSize(iSize) == false) {
        std::stringstream oSsLog;
        oSsLog << "Error while setting snake size. Size: " << iSize << " MaxSize: " << iMaxSize << "\n";
        cLog::getInstance().write(eServeriyLevel::Error, oSsLog.str());

        return (false);
    }   

    create(NX_SNAKE_START_X, NX_SNAKE_START_Y, eNXKeyPressed::right);

    return (true);
}

bool cSnake::setSize(const int iSize) {

    if (iSize > getMaxSize())
        return (false);

    m_iSize = iSize;

    return (true);
}

int cSnake::getSize() {

    return (m_iSize);
}

void cSnake::setMaxSize(const int iMaxSize) {

    m_iMaxSize = iMaxSize;
}

int cSnake::getMaxSize() {

    return (m_iMaxSize);
}

bool cSnake::increaseSize(const int iSize) {

    STSnakeBody stSnakeBody;

    stSnakeBody.x = m_oVector.front().x;
    stSnakeBody.y = m_oVector.front().y;
    
    stSnakeBody.isHead = false;
    stSnakeBody.isLastRemovedNode = false;

    m_oVector.push_back(stSnakeBody);

    return (setSize(getSize() + iSize));    
} 

void cSnake::render() {

    cLog::getInstance().write(eServeriyLevel::Debug, "Rendering snake.");

    if (m_bIsFirstRender == true) {
        for (STSnakeBody oStSnakeBody : m_oVector) {
            mvaddch(oStSnakeBody.y, oStSnakeBody.x, NX_SNAKE_BODY);
        }
    } else {
        if (m_oVector.front().isLastRemovedNode == true)        
            mvaddch(m_oVector.front().y, m_oVector.front().x, ' ');
            
        mvaddch(m_oVector.back().y, m_oVector.back().x, NX_SNAKE_BODY);
    }

    m_bIsFirstRender = false;
}

void cSnake::create(const int x, 
                    const int y,                     
                    eNXKeyPressed eNXDirection) {

    int i = 0;
    int iSnakeSize = 0;

    if (eNXDirection == eNXKeyPressed::left) {
        i = x;
        iSnakeSize = (x + NX_SNAKE_START_SIZE);
    } else {
        i = y;
        iSnakeSize = (y + NX_SNAKE_START_SIZE);
    }

    for (; i < iSnakeSize; ++i) {
        STSnakeBody stSnakeBody;

        if (eNXDirection == eNXKeyPressed::right) {        
            stSnakeBody.x = i;            
            stSnakeBody.y = y;
        } else {
            stSnakeBody.x = x;            
            stSnakeBody.y = i;
        }        

        if (i == iSnakeSize)
            stSnakeBody.isHead = true;
        else
            stSnakeBody.isHead = false;

        m_oVector.push_back(stSnakeBody);
    }

    m_eSnakeDirection = eNXDirection;
}

void cSnake::setDirection(eNXKeyPressed eNXMovDir) {    
    m_eSnakeDirection = eNXMovDir;
}

eNXKeyPressed cSnake::getDirection() {    
    return (m_eSnakeDirection);
}

STSnakeBody cSnake::getHeadPosition() {
    return (m_oVector.back());
}

void cSnake::move(eNXKeyPressed eNXMovDir) {
    if (eNXMovDir == eNXKeyPressed::undefined)
        eNXMovDir = getDirection();
    
    if (m_oVector.size() > 0) {
        STSnakeBody stSnakeBody;

        // Get the actual position of snake head.
        stSnakeBody.x = m_oVector.back().x;
        stSnakeBody.y = m_oVector.back().y;
        
        switch (eNXMovDir) {
            case eNXKeyPressed::left:
                
                if (getDirection() == eNXKeyPressed::right) {                
                    stSnakeBody.x++;
                    eNXMovDir = eNXKeyPressed::right;
                }
                else
                    stSnakeBody.x--;

                break;
            
            case eNXKeyPressed::right:

                if (getDirection() == eNXKeyPressed::left) {
                    stSnakeBody.x--;
                    eNXMovDir = eNXKeyPressed::right;
                }
                else
                    stSnakeBody.x++;

                break;

            case eNXKeyPressed::up:

                if (getDirection() == eNXKeyPressed::down) {                
                    stSnakeBody.y++;
                    eNXMovDir = eNXKeyPressed::down;
                }
                else
                    stSnakeBody.y--;
                
                break;

            case eNXKeyPressed::down:

                if (getDirection() == eNXKeyPressed::up) {                
                    stSnakeBody.y--;
                    eNXMovDir = eNXKeyPressed::up;
                }
                else
                    stSnakeBody.y++;

                break;

            default:
                // @TODO throw a error.
                break;
        }        
        
        if (m_oVector.front().isLastRemovedNode == true)
            m_oVector.erase(m_oVector.begin());            
        
        // Mark that the last node should be delete in the next movement.
        m_oVector.front().isLastRemovedNode = true;

        m_oVector.back().isHead = false;

        // Put in the body the new head position.
        stSnakeBody.isHead = true;
        m_oVector.push_back(stSnakeBody);

    } else {
        // @TODO throw a error.
        return;
    }

    setDirection(eNXMovDir);
}
    


