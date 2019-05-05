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

    logSnakeNodes();

    STSnakeBody stSnakeNode;

    // Create new snake head.
    stSnakeNode.x = m_odqSnakeNodes.back().x+1;
    stSnakeNode.y = m_odqSnakeNodes.back().y;    
    stSnakeNode.isHead = true;
    stSnakeNode.isLastRemovedNode = false;

    // Change the status of being head of last node.
    m_odqSnakeNodes.back().isHead = false;

    m_odqSnakeNodes.push_back(stSnakeNode);

    logSnakeNodes();

    return (setSize(getSize() + iSize));    
} 

void cSnake::render() {

    cLog::getInstance().write(eServeriyLevel::Debug, "Rendering snake.");

    if (m_bIsFirstRender == true) {
        for (STSnakeBody stSnakeNode : m_odqSnakeNodes) {
            mvwaddch(stdscr, stSnakeNode.y, stSnakeNode.x, NX_SNAKE_BODY);
        }
    } else {
        if (m_odqSnakeNodes.front().isLastRemovedNode == true)        
            mvwaddch(stdscr, m_odqSnakeNodes.front().y, m_odqSnakeNodes.front().x, NX_SNAKE_CLS);

        std::stringstream oLogStr;
        oLogStr << "y:" << m_odqSnakeNodes.back().y << "/" <<  m_odqSnakeNodes.at(m_odqSnakeNodes.size() - 2).y 
                << " x:" << m_odqSnakeNodes.back().x << "/" <<  m_odqSnakeNodes.at(m_odqSnakeNodes.size() - 2).x;
        cLog::getInstance().write(eServeriyLevel::Debug, oLogStr.str());

        mvwaddch(stdscr, m_odqSnakeNodes.back().y, m_odqSnakeNodes.back().x, NX_SNAKE_BODY);
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

        stSnakeBody.isLastRemovedNode = false;

        m_odqSnakeNodes.push_back(stSnakeBody);
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
    return (m_odqSnakeNodes.back());
}

void cSnake::move(eNXKeyPressed eNXMovDir) {
    if (eNXMovDir == eNXKeyPressed::undefined)
        eNXMovDir = getDirection();
    
    if (m_odqSnakeNodes.size() > 0) {
        STSnakeBody stSnakeBody;

        // Get the actual position of snake head.
        stSnakeBody.x = m_odqSnakeNodes.back().x;
        stSnakeBody.y = m_odqSnakeNodes.back().y;
        
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
        
        if (m_odqSnakeNodes.front().isLastRemovedNode == true)
            m_odqSnakeNodes.pop_front();
        
        // Mark that the last node should be delete in the next movement.
        m_odqSnakeNodes.front().isLastRemovedNode = true;

        m_odqSnakeNodes.back().isHead = false;

        // Put in the body the new head position.
        stSnakeBody.isHead = true;

        stSnakeBody.isLastRemovedNode = false;

        m_odqSnakeNodes.push_back(stSnakeBody);

    } else {
        // @TODO throw a error.
        return;
    }

    setDirection(eNXMovDir);
}


bool cSnake::checkSnakeBodyCollision() {    
    for (auto stSnakeNode : m_odqSnakeNodes) {
        if (stSnakeNode.isHead)
            continue;

        if (stSnakeNode.x == m_odqSnakeNodes.back().x &&
            stSnakeNode.y == m_odqSnakeNodes.back().y)
            return (true); // Collision detected.
    }

    return (false);
}
    
void cSnake::logSnakeNodes(){

    std::stringstream oSsSnakeNodes;

    oSsSnakeNodes << "Printing snake nodes:" << std::endl;

    for (auto stSnakeNode: m_odqSnakeNodes){
        oSsSnakeNodes << "Node: " 
                      << "x: [" << stSnakeNode.x << "] "
                      << "y: [" << stSnakeNode.y << "] "
                      << "head: [" << stSnakeNode.isHead << "] "
                      << "deadnode: [" << stSnakeNode.isLastRemovedNode << "]" << std::endl;
    }

    oSsSnakeNodes << "Print end.";

    cLog::getInstance().write(eServeriyLevel::Debug, oSsSnakeNodes.str());
}


