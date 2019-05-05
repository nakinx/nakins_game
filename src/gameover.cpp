#include "gameover.h"

#include "nakins.h"
#include "engine.h"
#include "log.h"

#include <sstream>

cGameOver::cGameOver() {

}

cGameOver::~cGameOver() {

}

bool cGameOver::initialize() {
    return (true);
}

void cGameOver::render() {
    cLog::getInstance().write(eServeriyLevel::Info, "Rendering gameover.");

    int iGameOverXBoardSize = 40;
    int iGameOverYBoardSize = 6;

    int iX = COLS;
    int iY = LINES;

    int iRightSideSize = ((iX - iGameOverXBoardSize) / 2);
    int iLeftSideSize = iRightSideSize + iGameOverXBoardSize;
    int iTopSideSize = ((iY - iGameOverYBoardSize) / 2);
    int iBottomSideSize = iTopSideSize + iGameOverYBoardSize;

    std::stringstream oSsLogTmp;

    oSsLogTmp << "Right Side Size: [" << iRightSideSize << "] Left Side Size: [" << iLeftSideSize << "] "
              << "Top Side Size: [" << iTopSideSize << "] Bottom Side Size: [" << iBottomSideSize << "] ";

    cLog::getInstance().write(eServeriyLevel::Info, oSsLogTmp.str()); 

    // Top horizontal line.
    for (int i = iRightSideSize; i < iLeftSideSize; ++i)
        {
        mvwaddch(stdscr, iTopSideSize, i, NX_WALL);
        }

    // Bottom horizontal line.
    for (int i = iRightSideSize; i < iLeftSideSize; ++i)
        {
        mvwaddch(stdscr, iBottomSideSize, i, NX_WALL);
        }

    // Right vertical line.
    for (int i = iTopSideSize; i < iBottomSideSize; ++i)
        {
        mvwaddch(stdscr, i, iRightSideSize, NX_WALL);
        }

    // Left vertical line.
    for (int i = iTopSideSize; i < iBottomSideSize; ++i)
        {
        mvwaddch(stdscr, i, iLeftSideSize - 1, NX_WALL);
        }

    int iGOBoardSideSize = (((iRightSideSize - iLeftSideSize) - oGameOver.length()) / 2);

    wmove(stdscr, (iTopSideSize + 2), iGOBoardSideSize);    
    waddstr(stdscr, oGameOver.c_str());    

}

