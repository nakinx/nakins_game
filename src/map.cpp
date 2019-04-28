#include "map.h"

#include "log.h"
#include "snake.h"

#include <random>
#include <sstream>

#define SNAKEFOODDEBUG 1

cMap::cMap() 
    : m_bIsDefaultMap(true),
      m_iEmptySpaceSize(0) {
}

cMap::~cMap() {
}

bool cMap::initialize(const int iChosenMap) {
    calculateEmptySpaceSize();
    return (true);
}

void cMap::calculateEmptySpaceSize() {
    if (m_bIsDefaultMap == true) 
        m_iEmptySpaceSize = (LINES - 2) * (COLS - 2);
}

int cMap::getEmptySpaceSize() {
    return (m_iEmptySpaceSize);
}

bool cMap::load() {
    if (m_bIsDefaultMap == true)
        return (true);    

    return (true);
}

void cMap::render() {
    if (m_bIsDefaultMap == true)
        border(NX_WALL, NX_WALL, NX_WALL, NX_WALL, NX_WALL, NX_WALL, NX_WALL, NX_WALL);            
}

bool cMap::checkResolution() {
    return (true);
}

void cMap::renderSnakeFood() {
    // @TODO - Separete food calculation of rendering.
#ifndef SNAKEFOODDEBUG
    unsigned int uiRINLine = randomIntegerNumber(2, (LINES - 2));
    unsigned int uiRINCol = randomIntegerNumber(2, (COLS - 2));
#else
    unsigned int uiRINLine = NX_SNAKE_START_Y;
    unsigned int uiRINCol = (NX_SNAKE_START_X + 8);
#endif

    std::stringstream oSsLog;
    oSsLog << "Randon Line [2/" << LINES << "]: " << uiRINLine << " Random Column [2/" << COLS << "]: " << uiRINCol;
    cLog::getInstance().write(eServeriyLevel::Debug, oSsLog.str());

    mvwaddch(stdscr, uiRINLine, uiRINCol, NX_SNAKE_FOOD);

    m_stSnakeFood.x = uiRINCol;
    m_stSnakeFood.y = uiRINLine;
    m_stSnakeFood.type = 0;
}

STSnakeFood cMap::getSnakeFoodPosition() {
    return (m_stSnakeFood);
}

void cMap::clearSnakeFoodPosition() {
    m_stSnakeFood.x = -1;
    m_stSnakeFood.y = -1;    
}

unsigned int cMap::randomIntegerNumber(const unsigned int iMin,
                                       const unsigned int iMax) {    
    std::random_device oRandomDevice;
    std::mt19937 mtEngine(oRandomDevice());
    std::uniform_int_distribution<> oUID(iMin, iMax);

    return (oUID(mtEngine));
}
