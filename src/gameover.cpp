#include "gameover.h"

#include "nakins.h"
#include "engine.h"
#include "log.h"

#include <sstream>

const std::string cGameOver::s_oGameOverMsg = "Game Over";
const std::string cGameOver::s_oGameOverKeyMsg = "Do wish to play again? Yes [ ] No [ ]";

const int cGameOver::s_iMsgXBoardSize = 42;
const int cGameOver::s_iMsgYBoardSize = 6;

cGameOver::cGameOver() 
    : m_iLeftSideSize(0),
      m_iRightSideSize(0),
      m_iTopSideSize(0),
      m_iBottomSideSize(0),
      m_iSelectedGameOverOption(eNXOption::yes) {
}

cGameOver::~cGameOver() {
}

bool cGameOver::initialize() {
    calcMsgBoardPos();
    return (true);
}

void cGameOver::render() {
    cLog::getInstance().write(eServeriyLevel::Info, "Rendering gameover.");

    // Clean board region and create right and left.
    for (int i = m_iTopSideSize; i <= m_iBottomSideSize; ++i) {
        for (int y = m_iLeftSideSize; y <= m_iRightSideSize; ++y) {
            if (y == m_iLeftSideSize)            
                mvwaddch(stdscr, i, y, NX_WALL);
            else if (y == m_iRightSideSize)
                mvwaddch(stdscr, i, y, NX_WALL);
            else
                mvwaddch(stdscr, i, y, NX_EMPTY);            
        }
    }

    // Top horizontal line.
    for (int i = m_iLeftSideSize; i <= m_iRightSideSize; ++i)
        {
        mvwaddch(stdscr, m_iTopSideSize, i, NX_WALL);
        }

    // Bottom horizontal line.
    for (int i = m_iLeftSideSize; i <= m_iRightSideSize; ++i)
        {
        mvwaddch(stdscr, m_iBottomSideSize, i, NX_WALL);
        }
    
    wmove(stdscr, (m_iTopSideSize + 2), calcMsgCenterPos(s_oGameOverMsg));    
    waddstr(stdscr, s_oGameOverMsg.c_str());

    wmove(stdscr, (m_iTopSideSize + 4), calcMsgCenterPos(s_oGameOverKeyMsg));    
    waddstr(stdscr, s_oGameOverKeyMsg.c_str());
}

void cGameOver::renderGameOverKeyOption() {
    cLog::getInstance().write(eServeriyLevel::Info, "Rendering key option.");

    int iYesPos = s_oGameOverKeyMsg.find('[') + 1 + calcMsgCenterPos(s_oGameOverKeyMsg); 
    int iNoPos = s_oGameOverKeyMsg.find_last_of('[') + 1 + calcMsgCenterPos(s_oGameOverKeyMsg);

    if (m_iSelectedGameOverOption == eNXOption::yes) {        
        wmove(stdscr, (m_iTopSideSize + 4), iYesPos); 
        waddstr(stdscr, "X"); 
        wmove(stdscr, (m_iTopSideSize + 4), iNoPos); 
        waddstr(stdscr, " ");          
    } else {
        wmove(stdscr, (m_iTopSideSize + 4), iYesPos); 
        waddstr(stdscr, " "); 
        wmove(stdscr, (m_iTopSideSize + 4), iNoPos); 
        waddstr(stdscr, "X");    
    }
}

void cGameOver::changeGameOverOption(const eNXKeyPressed oeNXKeyPressed) {
    if (oeNXKeyPressed == eNXKeyPressed::left ||
        oeNXKeyPressed == eNXKeyPressed::right) {
        if (m_iSelectedGameOverOption == eNXOption::yes) {
            m_iSelectedGameOverOption = eNXOption::no;
            cLog::getInstance().write(eServeriyLevel::Info, "Change to no!");
            }
        else
            {
            m_iSelectedGameOverOption = eNXOption::yes;
            cLog::getInstance().write(eServeriyLevel::Info, "Change to yes!");
            }
     }
}

void cGameOver::calcMsgBoardPos() {
    m_iLeftSideSize = ((NX_X - s_iMsgXBoardSize) / 2);
    m_iRightSideSize = m_iLeftSideSize + s_iMsgXBoardSize;
    m_iTopSideSize = ((NX_Y - s_iMsgYBoardSize) / 2);
    m_iBottomSideSize = m_iTopSideSize + s_iMsgYBoardSize;

    std::stringstream oLogTmp;

    oLogTmp << "Right Side Size: [" << m_iRightSideSize << "] Left Side Size: [" << m_iLeftSideSize << "] "
            << "Top Side Size: [" << m_iTopSideSize << "] Bottom Side Size: [" << m_iBottomSideSize << "] ";

    cLog::getInstance().write(eServeriyLevel::Info, oLogTmp.str()); 
}
 
int cGameOver::calcMsgCenterPos(const std::string oMsg) {
    return ((((m_iLeftSideSize - m_iRightSideSize) - oMsg.length()) / 2) + m_iRightSideSize + 1);
}
