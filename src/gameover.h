#ifndef GAMEOVER_H_
#define GAMEOVER_H_

#include "nakins.h"

#include <string>

class cGameOver {

const static std::string s_oGameOverMsg;
const static std::string s_oGameOverKeyMsg;

const static int s_iMsgXBoardSize; ///< Default x size of message board.
const static int s_iMsgYBoardSize; ///< Default y size of message board.

public:
    cGameOver();

    ~cGameOver();

    bool initialize();

    void render();

    void renderGameOverKeyOption();

    void changeGameOverOption(const eNXKeyPressed oeNXKeyPressed);

private:
    int m_iLeftSideSize; ///< Board left spacing.
    int m_iRightSideSize; ///< Board right spacing.
    int m_iTopSideSize; ///< Board top spacing.
    int m_iBottomSideSize; ///< Board bottom spacing.  
    eNXOption m_iSelectedGameOverOption; ///< Selected option on game over message board.  

    void calcMsgBoardPos();

    int calcMsgCenterPos(const std::string oMsg);    
};

#endif // GAMEOVER_H_