#include "topbar.h"
#include "log.h"

#include <iostream>
#include <sstream>
#include <iomanip>

cTopBar::cTopBar() 
    : m_uliRecord(0),
      m_uliScore(0) {

}

cTopBar::~cTopBar() {
}

bool cTopBar::initialize() {
    m_uliRecord = 0;
    m_uliScore = 0;

    return true;
}

void cTopBar::renderScore() { 
    std::stringstream oSsScore;
    
    oSsScore << "Score: " << std::noshowpoint << std::setfill ('0') << std::setw (SCORE_SPACE_SIZE - 7) << m_uliScore;
    
    wmove(stdscr, 0, (COLS - SCORE_SPACE_SIZE));    
    waddstr(stdscr, oSsScore.str().c_str());    
}

void cTopBar::renderRecord() {
    std::stringstream oSsScore;
    
    oSsScore << "Record: " << m_uliRecord;
    
    wmove(stdscr, 0, 1);    
    waddstr(stdscr, oSsScore.str().c_str());   
}

void cTopBar::increaseScore(const eScoreType oeScoreType, const unsigned int iSpeed) {

    switch (oeScoreType)
    {
    case eScoreType::food:
        m_uliScore += iSpeed * (unsigned int)eScoreType::food;
        break;
    
    case eScoreType::fruit:
        m_uliScore += iSpeed * (unsigned int)eScoreType::fruit;
        break;

    default:
        // @TODO - Treat exception.
        break;
    }

}
