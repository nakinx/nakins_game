#include "map.h"

#include "log.h"
#include "snake.h"

#include <random>
#include <sstream>

#define SNAKEFOODDEBUG 1

cMap::cMap() 
    : m_bIsDefaultMap(true),
      m_iEmptySpaceSize(0),
      m_uiX(0),
      m_uiY(0) {    
}

cMap::~cMap() {
}

bool cMap::initialize(const int iChosenMap) {
    m_uiX = COLS;    
    m_uiY = LINES; 

    std::stringstream oSsLog;
    oSsLog << "Resolution: " << m_uiX << "x" << m_uiY << ".";
    cLog::getInstance().write(eServeriyLevel::Info, oSsLog.str());

    calculateEmptySpaceSize();    

    return (true);
}

void cMap::calculateEmptySpaceSize() {
    if (m_bIsDefaultMap == true) 
        m_iEmptySpaceSize = (m_uiY - 2) * (m_uiX - 2);
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
    cLog::getInstance().write(eServeriyLevel::Info, "Rendering map.");

    // Remove one line at the top to score bar.
    for (int i = 1; i < (m_uiX - 1); ++i)
        mvwaddch(stdscr, 1, i, NX_WALL);

    // Remove two lines at the bottom to command.
    for (int i = 1; i < (m_uiX - 1); ++i)
        mvwaddch(stdscr, (m_uiY - 2), i, NX_WALL);

    // Remove one line at the top and bottom.
    for (int i = 1; i < (m_uiY - 1); ++i)
        mvwaddch(stdscr, i, 1, NX_WALL);

    // Remove one line at the top and bottom.
    for (int i = 1; i < (m_uiY - 1); ++i)
        mvwaddch(stdscr, i, (m_uiX - 2), NX_WALL);
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
